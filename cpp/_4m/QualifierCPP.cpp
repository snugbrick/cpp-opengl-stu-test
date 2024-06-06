#include <iostream>
using namespace std;

extern "C++" const int aaa = 1111; // 链接性为外部 以C++协议读取
const int aaaa = 1111;             // 链接性为内部
// 链接性为内部
template <typename T> static auto print(T a, T b) -> decltype(a + b);
static void print(int a); // 链接性为内部

struct test {
  int age;
  mutable double x;
};
struct newTest {
  char dross[20];
  int slag;
};

char buffer1[50];

auto main() -> int {
  const test newTry = {114, 11.4};
  const test *p;
  p = &newTry;
  cout << p->x << endl;
  p->x = 16.6;
  cout << p->x << endl;

  newTest *p1, *pd1;
  p1 = new newTest{};
  p1->slag = 114514;
  cout << &(p1->slag) << endl;
  pd1 = new (buffer1) newTest; // 使用new在buffer1中创建int
                               // buffer1是静态地址,不需要delete
  cout << &pd1 << endl;        // 0x61fdf8
  // pd1->slag = 1919810;
  // cout << &(pd1->slag) << endl;
  char *charP = buffer1;
  cout << &charP << endl; // 0x61fdf0
                          // 为什么相差8个字节 ?????
  delete p1;
  return 0;
}
static void print(int a) { cout << a << endl; }
