//
// Created by 杜航宇 on 2019-10-03.
//
// 测试析构函数

#include "iostream"
#include "StackWithMin.cpp"

namespace Test
{
    class Widget
    {
    public:
        Widget() = default;

        virtual ~Widget()
        {
            std::cout << "widget's destructor is running!" << std::endl;
        }

        bool operator<(const Widget &lhs)
        {
            return true;
        }

        bool operator<=(const Widget &lhs)
        {
            return true;
        }

        bool operator>(const Widget &lhs)
        {
            return true;
        }
    };
}

int main()
{
    StackWithMin<Test::Widget> stack_with_min;
    Test::Widget               widget;

    stack_with_min.push(widget);
}
