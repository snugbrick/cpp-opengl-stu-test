#include <iostream>
using namespace std;
namespace test {
void func(int a, int b); // func proto
int ta = 11;

void func(int a, int b) { std::cout << a + b << std::endl; }
}; // namespace test
namespace test2 {
namespace test3 {
void func2(int a, int b); // func proto
int ta2 = 12;
void func2(int a, int b) { std::cout << a - b << std::endl; }
} // namespace test3
} // namespace test2

char outSide[8] = {"outSide"};
int main() {
  cout << "this is namespace test" << endl;
  using namespace test; // 遇到相同会被覆盖
  // using test::func 遇到相同不会被覆盖
  test::func(1, 2);
  func(2, 3);

  test2::test3::func2(4, 2);

  char outSide[7] = {"inSide"};
  cout << outSide << endl;
  cout << ::outSide << endl;
  return 0;
}