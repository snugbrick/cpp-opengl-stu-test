#include "../_h/newTry.h"
#include <iostream>
using namespace std;

namespace newSpace {
int main() { return 0; }
void print() {}
} // namespace newSpace

int main() {
  cout << "this is a human" << endl;
  human *p;
  human realHuman = {NAME, 16};
  p = &realHuman;
  cout << p->name << endl;

  print(114514);
  return 0;
}
template <typename T> void print(T things) { cout << things << endl; }