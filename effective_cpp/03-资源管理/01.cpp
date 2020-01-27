#include "iostream"

class Widget
{
public:
    explicit Widget()
            : Widget(std::string("default"))
    {}

    explicit Widget(const std::string &name)
    :theName(name)
    {
        increment_id();
        std::cout << "default constructor is called, name == " << name
                  << ", id == " << id << std::endl;
    }

    ~Widget()
    {
        std::cout << "destructor is called, name == " << theName
                  << ",id = " << id << std::endl;
    }

    Widget(const Widget &w)
    {
        increment_id();
        std::cout << "copy constructor is called" << std::endl;
    }

    Widget &operator=(const Widget &rhs)
    {
        increment_id();
        std::cout << "copy assignment is called" << std::endl;
        return *this;
    }

private:
    static int id;
    std::string theName;

    static void increment_id()
    {
        ++id;
    }
};

int Widget::id = 0;

int main(int argc, char **argv)
{
    auto                    *w = new Widget("w1");
    std::unique_ptr<Widget> ptr(w);

    w = new Widget("w2");
    std::shared_ptr<Widget> sptr(w, [](Widget *wptr)
    {
        std::cout << "customized deleter is called!" << std::endl;
        delete wptr;
    });
}
