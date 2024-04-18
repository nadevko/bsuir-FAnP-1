#include <algorithm>
#include <fstream>
#include <iostream>
using namespace std;

struct STUDENT {
  string name;
  int numero;
  float performance[5];
  void print(STUDENT student, ofstream &file) {
    file << "name = " << student.name << "\nnumero = " << student.numero
         << "\nperformance = ";
    for (int j = 0; j < 5; j++)
      file << student.performance[j] << " ";
    file << endl;
  };
};

bool sorter(STUDENT &a, STUDENT &b) { return a.name < b.name; }

int main() {
  cout << "Сколько студентов хотите добавить? ";
  unsigned n;
  cin >> n;
  STUDENT *students = new STUDENT[n];

  for (unsigned i = 0; i < n; i++) {
    cin.ignore();
    STUDENT current;
    cout << "Фамилия и инициалы студента: ";
    getline(cin, current.name);
    cout << "Номер группы: ";
    cin >> current.numero;
    cout << "Успеваемость: \n";
    for (int i = 0; i < 5; i++) {
      cout << "\t" << i + 1 << ": ";
      cin >> current.performance[i];
    }
    students[i] = current;
  }

  sort(students, students + n, sorter);
  ofstream file;
  file.open("dist/students.ini");

  for (unsigned i = 0; i < n; i++) {
    file << "[" << i + 1 << "]\n";
    students[i].print(students[i], file);
    file << endl;
  }
  file.close();
  cout << "Данные успешно записаны в dist/students.ini";
}
