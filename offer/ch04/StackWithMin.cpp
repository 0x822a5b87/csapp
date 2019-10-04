//
// Created by 杜航宇 on 2019-10-03.
//

#include "iostream"
#include "stack"

template<typename T>
class StackWithMin
{
public:
    StackWithMin()
            : data(), min_data()
    {}

    virtual ~StackWithMin()
    {
        std::cout << "StackWithMin destructor is running!" << std::endl;
    }

    void push(T value)
    {
        if (data.empty())
        {
            data.push(value);
            min_data.push(value);
        }
        else
        {
            data.push(value);
            T min_value = min();
            // 这里必须注意，一定要有等于号，因为可能压入两个最小值
            if (value <= min_value)
            {
                min_data.push(value);
            }
        }
    }

    T pop()
    {
        T value = data.top();
        data.pop();
        T min_value = min_data.top();
        if (value == min_value)
        {
            min_data.pop();
        }
        return value;
    }

    T min() const
    {
        return min_data.top();
    }

private:
    std::stack<T> data;
    std::stack<T> min_data;
};
