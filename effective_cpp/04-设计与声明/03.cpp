#include "iostream"

class WidgetImpl
{
public:
    WidgetImpl(int name) : name(name)
    {}

public:
    int name;
};

class Widget
{
public:
    Widget(WidgetImpl *pImpl) : pImpl(pImpl)
    {}

    void swap(Widget &other)
    {
        std::cout << "widget member function: swap is running!" << std::endl;
        using std::swap;
        swap(pImpl, other.pImpl);
    }

    WidgetImpl *pImpl;
};

namespace std
{
    template <>
    void swap<Widget>(Widget &a, Widget &b) noexcept
    {
        std::cout << "std template<> function is running" << std::endl;
        a.swap(b);
    }
}

int main(int argc, char **argv)
{
    WidgetImpl wi1(1), wi2(2);
    Widget w1(&wi1), w2(&wi2);
    std::cout << w1.pImpl->name << " " << w2.pImpl->name << std::endl;
    std::swap(w1, w2);
    std::cout << w1.pImpl->name << " " << w2.pImpl->name << std::endl;
    //1 2
    //std template<> function is running
    //widget member function: swap is running!
    //2 1
}