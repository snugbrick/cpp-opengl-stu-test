#include <iostream>
using namespace std;

extern int global;

void other() {
  int *time = new int(114);
  time = &global;
  cout << *time << endl;
  delete time;
}