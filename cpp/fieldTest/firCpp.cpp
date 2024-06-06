#include "_h.h"
#include <iostream>
using namespace std;

int global = 100;
static int fileField = 200;

int main() {
  cout << "aa" << endl;
  other();
  return 0;
}