#include <cmath>
#include <iostream>
using namespace std;

bool is_solution(int x, int y, int z, int m) {
  return pow(x, 3) + pow(y, 3) + pow(z, 3) == m;
}

void print_solution(int x, int y, int z) {
  cout << x << ", " << y << ", " << z << endl;
}

void print_solutions(int m) {
  for (int x = 0; x <= cbrt(m); x++)
    for (int y = x; y <= cbrt(m); y++)
      for (int z = y; z <= cbrt(m); z++)
        if (is_solution(x, y, z, m))
          print_solution(x, y, z);
}

int main() {
  int m;
  cout << "Введите m: ";
  cin >> m;
  cout << "Решения для данного m:" << endl;
  print_solutions(m);
  return 0;
}
