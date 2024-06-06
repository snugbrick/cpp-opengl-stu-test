#include <iostream>
#include <ostream>
#ifndef CLASS_LOANG
#define CLASS_LOANG
#endif

using namespace std;

class FirTry {
private:
  enum class aYear : short { mon = 12, day = 30 };
  aYear newY = aYear::mon;
  int _money = int(newY); // private by defalt
  int check(int much) {
    if (much < 0) {
      cout << "y u much is a negative?" << endl;
      return 0;
    }
    return much;
  }

public:
  explicit FirTry(int money) {
    cout << _money << "here is constructor" << endl;
    _money = money;
  }; // auto inline
  ~FirTry() { std::cout << "bye" << std::endl; }
  void add(int much);
  void print() { cout << _money << endl; };
  FirTry operator&(FirTry &a) const {
    a._money += this->_money;
    return a;
  }
  friend ostream &operator<<(ostream &os, const FirTry &ft);
  const FirTry &maximun(const FirTry &ft2) const;
};
