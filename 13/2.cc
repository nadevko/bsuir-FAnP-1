#include "lib/shunting.cc"

int main() {
  cout << "Введите выражение: ";
  string str;
  getline(cin, str);
  try {
    ShuntingYard<int> shunting;
    auto result = shunting.calc(str);
    cout << "Результат: " << result << endl;
  } catch (const runtime_error &err) {
    cout << "Ошибка: " << err.what() << endl;
  }
}
