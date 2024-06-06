#include <iostream>
using namespace std;

template <typename T> void print(T a);
template <> void print<char>(char a);
template <typename T, typename U> void printWhat(T az, U b);
template void print(int a);

auto main() -> int {
  int a = 11;
  print(a);
  char name = 'a';
  print(name);

  int ab = 11;
  cout << &ab << endl;

  double az = 1.111;
  printWhat(az, ab);
  return 0;
}

template <typename T> void print(T a) { cout << a << endl; }
template <> void print<char>(char a) {
  cout << a << endl;
  cout << "看到我说明我优先级高" << endl;
}
template <typename T, typename U> void printWhat(T az, U b) {
  decltype(az + b) azPLASb = az + b; // double
  cout << typeid(azPLASb).name() << endl;

  typedef decltype((az + b)) azAND; // double &
  azAND aaa;
  cout << typeid(aaa).name() << endl;
}