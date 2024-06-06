#ifndef NAME
#define NAME "yap"
#endif

struct human {
  char name[5];
  int age;
};

template <typename T> void print(T things);