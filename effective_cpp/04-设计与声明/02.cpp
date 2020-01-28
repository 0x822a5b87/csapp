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

    Widget& operator=(const Widget& rhs)
    {
        increment_id();
        std::cout << "copy assignment is called" << std::endl;
        return *this;
    }

private:
    static int id;
    static void increment_id()
    {
        ++id;
    }
};

int Widget::id = 0;

Widget ret_widget()
{
    Widget w;
    std::cout << "w" << std::endl;
    return w;
}

int main(int argc, char **argv)
{
    Widget w = ret_widget();
    std::cout << "w2" << std::endl;
}
