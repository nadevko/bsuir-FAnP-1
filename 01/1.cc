#include <cmath>
#include <iostream>
using namespace std;

int main() {
  double first, second;
  cout << "Первое число: ";
  cin >> first;
  cout << "Второе число: ";
  cin >> second;
  cout << "Среднее арифметическое их квадратов: "
       << (pow(first, 2) + pow(second, 2)) / 2 << endl
       << "Среднее арифметическое их модулей: "
       << (fabs(first) + fabs(second)) / 2 << endl;
  return 0;
}
