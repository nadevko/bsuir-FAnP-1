#include <iostream>
using namespace std;

int main() {
  int n, arr[100][100], main = 0, secondary = 0;
  cout << "Введите размерность измерения двумерного массива ( <= 100): ";
  cin >> n;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> arr[i][j];
    }
  }
  for (int i = 0; i < n; i++) {
    main += arr[i][i];
    secondary += arr[i][n - i - 1];
  }
  cout << "Сумма главной диагонали: " << main << endl
       << "Сумма побочной диагонали: " << secondary << endl;
}
