#include "testhelper.h"
#include <iostream>

TestHelper::TestHelper(QObject *parent)
    : QObject(parent)
{

}

void TestHelper::received(int a, int b, int c, int d)
{
    std::cout << a << std::endl;
}
