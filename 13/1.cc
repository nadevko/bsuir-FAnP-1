#include <iomanip>
#include <iostream>
#include <map>
#include <stack>

using namespace std;

template <const bool checked = false, const bool ksis = false>
class ShuntingYard {
public:
  static string run(string input) {
    return (new ShuntingYard)->to_postfix(input);
  }
  string to_postfix(string infix) {
    shunting = {};
    postfix = "";
    rank = 0;
    length = infix.length();

    enum precedence prev = sum;
    for (auto symbol : infix) {
      enum precedence current = precedence[symbol];
      if (checked && !isspace(symbol) && current != open && current != close) {
        switch (prev) {
        case operand:
          if (current == operand)
            throw new runtime_error("Операнд после операнда");
          break;
        default:
          if (current != operand)
            throw new runtime_error("Оператор после оператора");
          break;
        }
        prev = current;
      }
      parse(symbol);
    }
    while (!shunting.empty())
      pop();
    if (postfix != "" && rank > 1)
      throw new runtime_error("Операндов больше, чем операций");
    cout << "| ␄ |     | " << setw(length) << postfix << " |\n";
    return postfix;
  }

private:
  enum precedence { operand, open, close, sum, multiply, power };
  map<char, precedence> precedence = {
      {'(', open},     {')', close},    {'+', sum},      {'-', sum},
      {'*', multiply}, {'/', multiply}, {'%', multiply}, {'^', power}};
  stack<char> shunting;
  uint rank;
  string postfix;
  size_t length;

  void parse(char symbol) {
    switch (precedence[symbol]) {
    case operand:
      if (isspace(symbol))
        break;
      postfix += symbol;
      rank++;
      break;
    case open:
      push(symbol);
      break;
    case close:
      while (true) {
        if (shunting.empty())
          throw new runtime_error("Скобки не закрыты");
        if (precedence[shunting.top()] == open)
          break;
        pop();
      }
      shunting.pop();
      break;
    default:
      push(symbol, precedence[symbol]);
      break;
    }
    cout << "| " << symbol << " | " << setw(3) << rank << " | " << setw(length)
         << postfix << " |\n";
  }
  void pop() {
    if (--rank < 1)
      throw new runtime_error("Операций больше, чем операндов");
    postfix += shunting.top();
    shunting.pop();
  }
  void push(char symbol) { shunting.push(symbol); }
  void push(char symbol, enum precedence prec) {
    while (!shunting.empty() && ((ksis) ? prec < precedence[shunting.top()]
                                        : prec <= precedence[shunting.top()]))
      pop();
    push(symbol);
  }
};

int main() {
  cout << "Введите выражение: ";
  string str;
  getline(cin, str);
  try {
    auto postfix = ShuntingYard<true, true>::run(str);
    cout << "Постфиксная форма: " << postfix << endl;
  } catch (const runtime_error *err) {
    cout << "Ошибка: " << err->what() << endl;
  }
}
