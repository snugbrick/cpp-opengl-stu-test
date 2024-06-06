#include "try.h"

Human::Human(int _age, char *_name)
{
  age = _age;
  name = _name;
}

Human::Human(const Human &others)
{
  age = others.age;
  name = others.name;
}

// Civilian
Civilian::Civilian(int value, Human &human)
    : money(value), Human(human)
{
  age = human.getAge();
  name = human.getName();
}

Civilian::Civilian(int _money, int _age, char *_name)
    : money(_money), Human(_age, _name)
{
  age = _age;
  name = _name;
}
