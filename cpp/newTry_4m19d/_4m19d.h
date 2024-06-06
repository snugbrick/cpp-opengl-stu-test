#ifndef _4m19d
#define _4m19d

class _4m19dVector {
private:
  enum class Numbers : short { Miracle, sun, zhang };
  int _x, _y, _z, _direction;

public:
  _4m19dVector(int x, int y, int z, int direction);
  friend _4m19dVector &operator+(_4m19dVector fir, _4m19dVector sec);
};

_4m19dVector::_4m19dVector(int x, int y, int z, int direction) {
  _x = x;
  _y = y;
  _z = z;
  _direction = direction;
}
#endif
