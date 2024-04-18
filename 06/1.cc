#include <iostream>
#include <cctype>
using namespace std;

int main() {
  string str;
  cout << "Введите строку: ";
  getline(cin, str);
  int len = 0, max = 1, pos = 0;
  for (unsigned long i = 0; i < str.length(); i++) {
    if (isspace(str[i]))
      len = 0;
    else {
      if (len == max) {
        max++;
        pos = i - len;
      }
      len++;
    }
  }
  cout << str.substr(pos, max) << endl;
}
