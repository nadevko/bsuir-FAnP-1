#include <cmath>
#include <iostream>
using namespace std;

int main() {
  double current, next;
  cout << "Введите 1-е число: ";
  cin >> current;

  cout << "Введите 2-е число: ";
  cin >> next;
  if (next < current)
    current = next;

  cout << "Введите 3-е число: ";
  cin >> next;
  if (next < current)
    current = next;

  cout << "Наименьшее число: " << current << endl;

  return 0;
}
