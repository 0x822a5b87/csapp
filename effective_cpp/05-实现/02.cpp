#include "iostream"

class Widget
{
public:
    int x;
    int y;
    int z;

    Widget(int a, int b, int c)
    :x(a), y(b), z(c)
    {

    }

    // 虚构造器不能少，否则不是多态的。那么不允许执行 dynamic_cast
    virtual ~Widget()
    {
        std::cout << "destructor is called" << std::endl;
    }
};

class Derived:public Widget
{
public:
    Derived(int a, int b, int c)
    :Widget(a, b, c)
    {}
};

class NotDerived
{
public:
    virtual ~NotDerived(){};
};

int main(int argc, char **argv)
{
//    const Widget &w = Widget(1, 2, 3);
//
//    std::cout << w.x << " x" << w.y << " " << w.z << std::endl;

    Widget *w1 = new Derived(1, 2, 3);
    NotDerived *nw = new NotDerived;

    if (Derived *dp = dynamic_cast<Derived*>(w1))
    {
        std::cout << "cast Widget* to Derived* successfully" << std::endl;
    }
    else
    {
        std::cout << "cast Widget* to Derived* fail" << std::endl;
    }

    if (Derived *dp = dynamic_cast<Derived*>(nw))
    {
        std::cout << "cast NotDerived* to Derived* successfully" << std::endl;
    }
    else
    {
        std::cout << "cast NotDerived* to Derived* fail" << std::endl;
    }

    delete w1;
    delete nw;
}