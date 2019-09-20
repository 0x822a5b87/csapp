//
// Created by 杜航宇 on 2019-09-19.
//

#include "iostream"

using std::chrono::milliseconds;
using std::chrono::duration_cast;
using std::chrono::system_clock;

long long FibonacciRec(unsigned int n)
{
    if (n <= 0)
    {
        return 0;
    }

    if (n == 1)
    {
        return 1;
    }

    return FibonacciRec(n - 2) + FibonacciRec(n - 1);
}

long long Fibonacci(unsigned int n)
{
    if (n <= 0)
    {
        return 0;
    }

    if (n == 1)
    {
        return 1;
    }

    long long result = 0;
    long long fibMinusOne = Fibonacci(1);
    long long fibMinusTwo = Fibonacci(0);
    for (int i = 2; i <= n; ++i)
    {
        result = fibMinusOne + fibMinusTwo;
        long long fib = fibMinusOne + fibMinusTwo;
        fibMinusTwo = fibMinusOne;
        fibMinusOne = fib;
    }

    return result;
}

int main()
{
    for (int i = 0; i < 10; ++i)
    {
        assert(FibonacciRec(i) == Fibonacci(i));
    }

    int num = 0x2b;
    milliseconds now = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
    FibonacciRec(num);
    milliseconds end = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
    std::cout << (end.count() - now.count()) << std::endl;

    now = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
    Fibonacci(num);
    end = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
    std::cout << (end.count() - now.count()) << std::endl;
}
