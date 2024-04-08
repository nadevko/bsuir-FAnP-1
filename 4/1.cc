#include <iostream>
using namespace std;

int main() {
  int n;
  double product = 1, arr[100];
  cout << "Введите размерность массива ( <= 100): ";
  cin >> n;
  for (int i = 0; i < n; i++) {
    cout << i + 1 << ": ";
    cin >> arr[i];
  }
  for (int i = 1; i < n; i = i + 2)
    product *= arr[i];
  cout << "Произведение чётных: ";
  cout << product << endl;
}
