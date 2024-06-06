#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "try.h"
#include <iostream>
#include <string.h>

using std::cout;
using std::endl;

int main()
{
    Human *newHu = new Human(17, "Mrzhang");
    Human newHu2(18, "MrMao");

    Human *newCiv = new Civilian(114514, *(newHu));
    cout << newCiv->getAge() << endl;

    newHu2 = *(newHu);

    int a = 0;
    cout << newHu2.getAge() << endl;
    // cout居然会自动打印char数组了 :/
    cout << newHu2.getName() << endl;

    a++;

    delete newCiv;
    delete newHu;
}