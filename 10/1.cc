#include <iostream>
using namespace std;

template <typename T> struct Sortable {
  size_t max;
  T *arr;
  auto operator[](size_t idx) { return arr[idx]; }
  auto operator>(const Sortable<T> &rhs) { return arr[0] > rhs.arr[0]; }
};

template <typename T> Sortable<T> *make_matrix(int cols, int rows) {
  auto arr = new Sortable<T>[cols];
  auto maxes = new size_t[cols];
  for (auto col = 0; col < cols; col++)
    arr[col].arr = new T[rows];
  for (auto row = 0; row < rows; row++)
    for (auto col = 0; col < cols; col++) {
      cin >> arr[col].arr[row];
      if (arr[col][row] > arr[col][maxes[col]])
        maxes[col] = row;
    }
  for (auto col = 0; col < cols; col++)
    arr[col].max = maxes[col];
  return arr;
}

template <typename T> void print(Sortable<T> *arr, int cols, int rows) {
  for (auto row = 0; row < rows; row++) {
    cout << endl;
    for (auto col = 0; col < cols; col++)
      cout << arr[col][row] << " ";
  }
}

template <typename T> void shaker(T *arr, int left, int right) {
  if (left >= right)
    return;
  for (auto i = left; i < right; i++)
    if (arr[i] > arr[i + 1])
      swap(arr[i], arr[i + 1]);
  for (auto i = --right; i > left; i--)
    if (arr[i - 1] > arr[i])
      swap(arr[i - 1], arr[i]);
  shaker<T>(arr, ++left, right);
}

template <typename T> void shaker(T *arr, unsigned lenght) {
  shaker(arr, 0, lenght - 1);
}

int main() {
  int rows, cols;
  cout << "Введите число строк: ";
  cin >> rows;
  cout << "Введите число столбцов: ";
  cin >> cols;

  auto arr = make_matrix<int>(cols, rows);
  cout << "Составлена матрица " << rows << "x" << cols << ": \n";
  shaker(arr, cols);
  print(arr, cols, rows);
}
