#include <cmath>
#include <iostream>
using namespace std;

int main() {
  double previous, current = 0, sum = 0;
  int n = 1;
  do {
    previous = current;
    current = pow(-1, n) / (3 * pow(n, 2));;
    sum += current;
    n++;
  } while (abs(current - previous) >= 0.0001);
  cout << sum << endl;
  return 0;
}
