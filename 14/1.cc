#include <functional>
#include <iomanip>
#include <iostream>
#include <queue>

using namespace std;

template <regular T> class Tree {
private:
  enum traversal { NLR, LNR, LRN };
  template <regular K> struct Node {
    K value;
    Node *left = nullptr, *right = nullptr;
    void add(Node &node) { add(node, value < node.value); }
    void add(Node &node, bool isRight) {
      auto target = isRight ? &right : &left;
      if (*target == nullptr)
        *target = &node;
      else
        (*target)->add(node);
    }
    void visit(function<void(T)> callback, traversal type = NLR) {
      if (type == NLR)
        callback(value);
      if (left != nullptr)
        left->visit(callback);
      if (type == LNR)
        callback(value);
      if (right != nullptr)
        right->visit(callback);
      if (type == LRN)
        callback(value);
    }
  };

public:
  Node<T> *root = nullptr;
  void add(T data) {
    auto node = new Node<T>(data);
    if (root == nullptr)
      root = node;
    else
      root->add(*node);
  }
  void print() {
    root->visit([](T value) { cout << value << endl; }, LNR);
  }
  auto operator==(Tree &rhs) {
    queue<T> values;
    root->visit([&](T value) { values.push(value); });
    try {
      rhs.root->visit([&](T value) {
        if (value != values.front())
          throw false;
        values.pop();
      });
    } catch (bool &result) {
      return result;
    }
    return true;
  }
};

template <typename T> istream &operator>>(istream &is, Tree<T> &tree) {
  T data;
  is >> data;
  tree.add(data);
  return is;
}

template <typename T> Tree<T> mkTree(string name) {
  Tree<T> tree;
  size_t size;
  cout << "Введите размер дерева " << name << ": ";
  cin >> size;
  for (size_t i = 1; i <= size; i++) {
    cout << "№" << setw(2) << i << ": ";
    cin >> tree;
  }
  return tree;
}

int main() {
  auto a = mkTree<int>("A");
  a.print();
  auto b = mkTree<int>("B");
  b.print();
  cout << "Деревья " << ((a == b) ? "одинаковы" : "разные") << endl;
}
