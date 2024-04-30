#include "lib/shunting.cc"

int main() {
  cout << "Введите выражение: ";
  string str;
  getline(cin, str);
  try {
    ShuntingYard<int, true, true> shunting;
    auto result = shunting.parse(str);
    cout << "Постфиксная форма: " << result << endl;
  } catch (const runtime_error &err) {
    cout << "Ошибка: " << err.what() << endl;
  }
}
