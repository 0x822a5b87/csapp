#include "iostream"

class Base
{
public:
    virtual void print() const
    {
        std::cout << "base print" << std::endl;
    }
};

class Derived:public Base
{
public:
    void print() const override
    {
        std::cout << "derived print" << std::endl;
    }
};

void do_print(Base base)
{
    base.print();
}

void do_print_const_ref(const Base &base)
{
    base.print();
}

int main(int argc, char **argv)
{
    Derived derived;
    do_print(derived);
    // base print
    do_print_const_ref(derived);
    // derived print
}