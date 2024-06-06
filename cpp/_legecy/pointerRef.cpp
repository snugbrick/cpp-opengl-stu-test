#include <iostream>
using namespace std;

char *cutString(const char *str, int len);
void printEnd(int a);
void (*ps)(int a); // 函数指针
void tryagain(char &a, int b);

int main() {
  cout << "main thread" << endl;
  char name[11] = "MaxPointer";
  char *psf = cutString(name, 3);
  cout << psf << endl;
  delete[] psf;

  ps = printEnd;
  (*ps)(114514);

  char namespacea = 'a';
  int a = 1;
  tryagain(namespacea, a);
  cout << namespacea << endl;

  return 0;
}
char *cutString(const char *str, int len) {
  if (len < 0) {
    len = 0;
  }
  char *p = new char[len + 1];
  p[len + 1] = '\0';
  for (int i = 0; i < len && str[i]; i++) {
    p[i] = str[i];
  }
  return p;
}
void printEnd(int a) {
  cout << "here is End , every thing death!" << a << endl;
}
void tryagain(char &a, int b) {
  cout << typeid(a).name() << endl;
  a = 'b';
}