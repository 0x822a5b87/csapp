#include "iostream"

class Base
{
    int a, b, c;
};

class Derived: public Base
{
    int x, y, z;
};

int main(int argc, char **argv)
{
    auto *d = new Derived;

    auto *b = (Derived *) d;

    std::cout << "d = " << d << ", b = " << b << std::endl;
    std::cout << "(d - b) = " << (d - b) << std::endl;
}