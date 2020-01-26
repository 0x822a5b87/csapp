//
// Created by 杜航宇 on 2020/1/26.
//

#include "iostream"

namespace _01
{
    class Widget
    {
    public:
        explicit Widget()
        :Widget(std::string("default"))
        {}

        explicit Widget(const std::string &name)
        {
            increment_id();
            std::cout << "default constructor is called, name == " << name << std::endl;
        }

        Widget(const Widget &w)
        {
            increment_id();
            std::cout << "copy constructor is called" << std::endl;
        }

        const Widget& operator=(const Widget& rhs)
        {
            increment_id();
            std::cout << "copy assignment is called" << std::endl;
            return rhs;
        }

    private:
        static int id;
        void increment_id()
        {
            ++id;
        }
    };

    int Widget::id = 0;

    class Container
    {
    public:
        Container(const std::string &name)
        :w0(name)
        {
            std::cout << "a == " << a << std::endl;
            std::cout << "b == " << b << std::endl;
        }

    private:
        Widget w1;
        Widget w0;
        int a;
        int b;
    };

    class ConstTest
    {
    public:
        void const_say() const
        {
            std::cout << "const say is called!" << std::endl;
        }

        void say()
        {
            std::cout << "say is called!" << std::endl;
        }
    };
}

int main(int argc, char **argv)
{
    _01::Container c(std::string("hello"));
}
