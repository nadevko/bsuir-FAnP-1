#include <cmath>
#include <iostream>
using namespace std;

float P(float n, float i = 1) {
  return (i > n) ? 0 : sqrt(2 * i + P(n, i + 1));
}

int main() {
  float n;
  cout << "Введите N: ";
  cin >> n;
  cout << "Для N равного " << n << " выражение равно " << P(n) << endl;
}
