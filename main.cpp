#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

class DataManager {
 private:
  int* data;
  int size;

 public:
  DataManager(int s) : data(nullptr), size(s) {
    if (size < 0) size = 0;

    data = new int[size];

    for (int i = 0; i < size; i++) {
      if (i % 2 == 0)
        data[i] = i * 2;
      else
        data[i] = 0;
    }
  }

  DataManager(const DataManager& other) : data(nullptr), size(other.size) {
    data = new int[size];
    for (int i = 0; i < size; i++) {
      data[i] = other.data[i];
    }
  }

  DataManager& operator=(const DataManager& other) {
    if (this != &other) {
      int* newData = new int[other.size];
      for (int i = 0; i < other.size; i++) {
        newData[i] = other.data[i];
      }

      delete[] data;
      data = newData;
      size = other.size;
    }
    return *this;
  }

  void print() const {
    for (int i = 0; i < size; i++) {
      cout << data[i] << " ";
    }
    cout << endl;
  }

  int getValue(int index) const {
    if (index >= 0 && index < size) return data[index];
    return 0;
  }

  ~DataManager() { delete[] data; }
};

void unsafeFunction() {
  char buffer[10];
  strcpy(buffer, "safe");
  cout << buffer << endl;
}

int compute(int x) {
  int result = 0;

  if (x > 10)
    result = x * 2;
  else if (x < 0)
    result = 0;
  else
    result = x;

  return result;
}

void memoryLeakDemo() {
  int* leak1 = new int[100];
  int* leak2 = new int;

  leak1[0] = 10;
  *leak2 = 20;

  cout << leak1[0] + *leak2 << endl;

  delete[] leak1;
  delete leak2;
}

void vectorIssues() {
  vector<int> v;

  v.push_back(1);
  v.push_back(2);

  cout << v[1] << endl;

  v.clear();

  if (!v.empty())
    cout << v.front() << endl;
  else
    cout << "vector is empty" << endl;
}

int main() {
  DataManager dm(5);

  dm.print();

  unsafeFunction();

  cout << compute(5) << endl;

  memoryLeakDemo();

  vectorIssues();

  DataManager dm2 = dm;

  cout << dm2.getValue(2) << endl;

  return 0;
}
