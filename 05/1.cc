#include <iostream>
using namespace std;

int main() {
  int n, main = 0, secondary = 0;
  cout << "Введите длинну измерения двумерного массива: ";
  cin >> n;
  int **arr = new int *[n];
  for (int i = 0; i < n; i++) {
    arr[i] = new int[n];
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
