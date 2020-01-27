#include "iostream"

class Test03
{
public:
    Test03()
    {
        std::cout << "constructor is running" << std::endl;
    }

    Test03(const Test03 &w)
    {
        std::cout << "copy constructor is called" << std::endl;
    }

    const Test03& operator=(const Test03& rhs)
    {
        std::cout << "copy assignment is called" << std::endl;
        return rhs;
    }
};


class Test04
{
public:
    Test04()
    {
        std::cout << "04 constructor is running" << std::endl;
    }

private:
    Test03 t;
};

int main(int argc, char **argv)
{
    Test04 t0;
    Test04 t1;

    t0 = t1;

    Test04 t2(t0);
}
