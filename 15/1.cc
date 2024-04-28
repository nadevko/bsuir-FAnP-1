#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

const size_t LIMIT = 2000;
const size_t KEYSIZE = 16;

template <typename K, typename T, size_t LIMIT = LIMIT> class HashMap {
public:
  struct Node {
    Node() {}
    Node(K key, T value) : key(key), value(value) {}
    K key;
    T value;
    Node *next = nullptr;

    size_t count() { return (next == nullptr) ? 1 : 1 + next->count(); }

    void insert(Node &node) {
      if (next == nullptr)
        next = &node;
      else
        next->insert(node);
    }

    Node *erase(K _key, T _value) {
      if (key == _key && value == _value)
        return next;
      if (next != nullptr)
        next = next->erase(_key, _value);
      return this;
    }

    void find(K _key, vector<T> *vec) const {
      if (key == _key)
        vec->push_back(value);
      if (next != nullptr)
        next->find(_key, vec);
    }
  };

  struct Iterator {
    using difference_type = ptrdiff_t;
    using element_type = Node *;
    using pointer = element_type *;
    using reference = element_type &;

  private:
    pointer ptr, start, stop;
    static_assert(sentinel_for<decltype(stop), decltype(ptr)>);

  public:
    Iterator() {}
    Iterator(pointer p, pointer s) : ptr(p), start(p), stop(s) {}
    reference operator*() const { return *ptr; }

    Iterator &operator++() {
      ++ptr;
      return *this;
    }
    Iterator operator++(int) {
      auto temp = *this;
      ++*this;
      return temp;
    }

    auto operator<=>(const Iterator &rhs) const = default;
    auto begin() {
      while (start != stop && *start == nullptr)
        start++;
      return start;
    }
    auto end() { return stop; }
  };
  auto begin() { return iter.begin(); }
  auto end() { return iter.end(); }

  void insert(Node &node) {
    auto key = hash<K>{}(node.key);
    if (memory[key] == nullptr)
      memory[key] = &node;
    else
      memory[key]->insert(node);
  }
  void insert(K key, T value) { insert(*new Node{key, value}); }

  void erase(K key, T value) {
    auto index = hash<K>{}(key);
    if (memory[index] == nullptr)
      return;
    auto node = memory[index]->erase(key, value);
    if (node != nullptr)
      memory[index] = node;
  }

  vector<T> find(K key) const {
    vector<T> vec;
    auto index = hash<K>{}(key);
    if (memory[index] != nullptr)
      memory[index]->find(key, &vec);
    return vec;
  }
  vector<T> operator[](K key) const { return find(key); }

private:
  Node *memory[LIMIT] = {};
  static_assert(forward_iterator<Iterator>);
  Iterator iter = Iterator(memory, std::end(memory));
};

template <> struct std::hash<string> {
  size_t operator()(const string &key) const noexcept {
    size_t result = 0;
    for (size_t i = 1; i <= key.length(); i++)
      result += pow(key[i - 1], 2) / 3 / i;
    return static_cast<size_t>(pow(result, 2)) / 100 % LIMIT;
  }
};

string randstr(size_t size) {
  auto chars = new char[size];
  for (size_t i = 0; i < size; i++) {
    enum charclasses {
      num,
      upper,
      lower
    } charClass = static_cast<charclasses>(rand() % 3);
    chars[i] = ((charClass == lower)   ? '_'
                : (charClass == upper) ? 'A'
                                       : '0') +
               rand() % ((charClass == lower)   ? 28
                         : (charClass == upper) ? 26
                                                : 10);
  }
  string str(chars);
  return str;
}

int main() {
  srand(time(NULL));
  size_t length = 0;
  size_t counts = 0;

  HashMap<string, int> map;
  for (size_t i = 0; i < LIMIT * 3; i++)
    map.insert(randstr(KEYSIZE), i);

  for (auto i : map)
    if (i != nullptr) {
      cout << "| " << setw(KEYSIZE) << i->key << " | " << setw(4) << i->value
           << " | " << setw(6) << i->count() << " |\n";
      length++;
      counts += i->count();
    }

  const string title3long = "ключ";
  const string title3 = (KEYSIZE < title3long.size()) ? "1" : title3long;
  cout << "|" << setw(1 + title3.length() + (KEYSIZE - title3.length() / 2) / 2)
       << title3
       << setw(string("| знач | кол-во ||\n").size() +
               (KEYSIZE - title3.length() / 2) / 2 +
               (KEYSIZE - title3.length() / 2) % 2)
       << "| знач | кол-во |\n"
       << "Было использовано " << length << " ячеек\n"
       << "Средняя глубина: " << (double)counts / length << endl;

  string key;
  cout << "Введите ключ: ";
  cin >> key;
  auto found = map[key];
  for (auto i : found)
    cout << i << endl;
}
