//
// Created by 杜航宇 on 2020/1/20.
//

#include "iostream"

class Widget
{
public:
    Widget()
    {
        std::cout << "default constructor is called" << std::endl;
    }

    Widget(const Widget &w)
    {
        std::cout << "copy constructor is called" << std::endl;
    }

    const Widget& operator=(const Widget& rhs)
    {
        std::cout << "copy assignment is called" << std::endl;
        return rhs;
    }
};

int main(int argc, char **argv)
{
    Widget w;
    Widget w1(w);
    Widget w2 = w1;
    w2 = w1;
}
