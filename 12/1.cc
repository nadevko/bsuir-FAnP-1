#include <iostream>
#include <queue>
using namespace std;

template <typename T> size_t get_max() {
  allocator<queue<T>> allocator;
  return allocator.max_size() / sizeof(T);
}

int main() {
  cout << "Максимальное количество элементов в вещественной очереди: "
       << get_max<double>();
}
