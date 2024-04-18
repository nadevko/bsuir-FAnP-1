#include <iomanip>
#include <iostream>
using namespace std;

int sum(int first, int second) { return first + second; }

double sum(double first, double second) { return first + second; }

double *sum(double *arr, double r1, double r2, double i1, double i2) {
  arr[0] = sum(r1, r2);
  arr[1] = sum(i1, i2);
  return arr;
}

int main() {
  string input;
  cout << "Введите выражение (int+int или double+doublei+double+doublei): ";
  getline(cin, input);
  if (input.find('i') == string::npos) {
    int first, second;
    sscanf(input.c_str(), "%i+%i", &first, &second);
    cout << "Результат: " << sum(first, second) << endl;
  } else {
    double r1, r2, i1, i2;
    sscanf(input.c_str(), "%lf+%lfi+%lf+%lfi", &r1, &i1, &r2, &i2);
    double arr[2];
    sum(arr, r1, r2, i1, i2);
    cout << "Результат: " << arr[0] << "+" << arr[1] << "i\n";
  }
}
