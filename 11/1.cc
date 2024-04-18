#include <functional>
#include <iomanip>
#include <iostream>

using namespace std;

const unsigned MAX = 7;

struct List {
  unsigned Sps[2][MAX] = {0};
  unsigned iterate(function<void(unsigned)> iteratable) {
    if (Sps[0][0] == 0)
      return 0;
    unsigned i = 0;
    while (true) {
      iteratable(i);
      if (Sps[1][i] == 0)
        return i;
      else
        i = Sps[1][i];
    };
  }
  unsigned alloc() {
    unsigned i = 0;
    while (Sps[0][i] != 0 || Sps[1][i] != 0)
      i++;
    return i;
  }
  void insert(unsigned num, unsigned current) {
    auto empty = alloc();
    Sps[0][empty] = num;
    Sps[1][empty] = Sps[1][current];
    Sps[1][current] = empty;
  }
  void append(unsigned num) {
    insert(num, iterate([](auto i) { (void)i; }));
  }
  void print(string message) {
    cout << "\033[1m" << message << "...";
    cout << "\n|\033|Список   |\n|Указатель|\n|Индекс   |\033[0m";
    iterate([this](auto i) {
      cout << "\033[2A" << setw(4) << Sps[0][i] << "|";
      cout << "\033[5D\033[B" << setw(4) << Sps[1][i] << "|";
      cout << "\033[5D\033[B" << setw(4) << i << "|";
    });
    cout << "\n\n";
  }
  unsigned findPointer(unsigned value) {
    unsigned pointer;
    iterate([this, &pointer, value](auto i) {
      if (Sps[0][i] == value)
        pointer = i;
    });
    return pointer;
  }
  unsigned findValue(unsigned pointer) {
    unsigned value;
    iterate([this, &value, pointer](auto i) {
      if (i == pointer)
        value = Sps[0][i];
    });
    return value;
  }
  void remove(unsigned pointer) {
    iterate([pointer, this](auto i) {
      if (Sps[1][i] == pointer) {
        Sps[1][i] = Sps[1][pointer];
        Sps[0][pointer] = 0;
        Sps[1][pointer] = 0;
      };
    });
  }
};

int main() {
  List list;

  for (unsigned i = 0; i < 6; i++)
    list.append(2 * i + 1);
  list.print("Добавление 6-ти элементов: 1, 3, 5, 7, 9, 11");

  list.remove(list.findPointer(9));
  list.print("Удаление элемента со значением 9");

  list.insert(13, list.findPointer(11));
  list.print("Добавление элемента 13 после элемента со значением 11");

  list.insert(15, list.findPointer(3));
  list.print("Добавление элемента 15 после элемента со значением 3");
}
