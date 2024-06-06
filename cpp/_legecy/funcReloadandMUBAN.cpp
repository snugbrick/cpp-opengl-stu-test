#include <iostream>
using namespace std;

// 函数模板 当没有隐式、显式具体化模板时，根据此创造隐式实例化
template <typename T> void print(T a) { cout << a << endl; };
// 具体化模板,当实例化时与具体化模板对应，则会立即使用具体化模板，而非函数模板
template <> void print<char>(char a);
// 显式实例化，编译器会根据此创造实例化模板
template void print<int>(int);

template <typename T> T add(T a, T b) { return a + b; }

void print(int a, double b);
struct test {
  char name[3];
  int age;
} firTry{"aa", 11}, secTry{"vv", 11};

union test2 {
  char name[3];
  int age;
} firTry2{14};

int main() {
  cout << "funcReload" << endl;
  print(1);
  print(1, 1.1);

  test p = {"hi", 14};
  test *ps = &firTry;
  cout << ps->age << endl;

  test2 p2 = {"bb"};
  cout << p2.name << endl;
  p2.age = 145;
  cout << p2.age << endl;

  return 0;
}
template <> void print<char>(char a) { cout << a << endl; }
void print(int a, double b) { cout << a + b << endl; }