#include <iostream>
#include <memory>
#include <queue>
using namespace std;

template <typename T> size_t get_max() {
  const auto alloc = new allocator<queue<double>>();
  const auto traits = new allocator_traits<queue<T>>;
  return traits->max_size(*alloc->allocate(0));
}

int main() {
  cout << "Максимальное количество элементов в вещественной очереди: "
       << get_max<double>();
}
