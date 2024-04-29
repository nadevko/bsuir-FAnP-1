#include <format>
#include <iomanip>
#include <iostream>
#include <map>
#include <stack>

using namespace std;

template <regular T, const bool checked = false, const bool ksis = false>
class ShuntingYard {
  enum precedence { operand, open, close, sum, multiply };
  map<char, precedence> precedence = {{'(', open},     {')', close},
                                      {'+', sum},      {'-', sum},
                                      {'*', multiply}, {'/', multiply}};
  stack<char> shunting;
  uint rank;
  string postfix;
  size_t length;

public:
  static string run(string input) { return (new ShuntingYard)->parse(input); }
  string parse(string infix) {
    shunting = {};
    postfix.clear();
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
    if (!postfix.empty() && rank > 1)
      throw new runtime_error("Операндов больше чем операций");
    cout << "| ␄ |     | " << setw(length) << postfix << " |\n";
    return postfix;
  }

  int calc(string input) {
    stack<T> stack;
    string operand;

    for (char c : input)
      if (isdigit(c))
        operand += c;
      else if (isspace(c)) {
        if (!operand.empty()) {
          stack.push(stod(operand));
          operand.clear();
        }
      } else if (operand.empty()) {
        if (stack.size() < 2)
          throw runtime_error("Операндов меньше чем операций");
        auto b = stack.top();
        stack.pop();
        auto a = stack.top();
        stack.pop();
        stack.push(calc(a, b, c));
        operand.clear();
      } else
        throw runtime_error("Неверный формат числа");
    if (!operand.empty())
      stack.push(stod(operand));
    if (stack.size() != 1)
      throw runtime_error("Операндов больше чем операций");
    return stack.top();
  }

private:
  double calc(T a, T b, char operation) {
    switch (operation) {
    case '+':
      return a + b;
    case '-':
      return a - b;
    case '*':
      return a * b;
    case '/':
      if (b == 0)
        throw runtime_error("Деление на ноль");
      return a / b;
    default:
      throw runtime_error(format("Оператор {} не определён", operation));
    }
  }

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
