#include "iostream"

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
    static void increment_id()
    {
        ++id;
    }
};

int Widget::id = 0;

int main(int argc, char **argv)
{
    Widget t0{};
    Widget t1{};

    t0 = t1;

    t0 = Widget();
}