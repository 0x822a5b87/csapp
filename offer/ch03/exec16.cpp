//
// Created by 杜航宇 on 2019-09-25.
//

#include "iostream"

// 要考虑一下几个情况
// 1. double 类型的比较问题
// 2. base 为 0 的情况。如果 base == 0，那么 exponent <= 0 都是无意义的
double Power(double base, int exponent)
{
    if (base == 0 && exponent <= 0)
    {
        return 0;
    }

    double ret = 1.0;
    if (exponent > 0)
    {
        for (int i = 0; i != exponent; ++i)
        {
            ret *= base;
        }
    }

    if (exponent < 0)
    {
        for (int i = 0; i != -exponent; ++i)
        {
            ret /= base;
        }
    }

    return ret;
}

bool equal(double num1, double num2)
{
    if ((num1 - num2 > -0.0000001) && (num1 - num2 < 0.0000001))
        return true;
    else
        return false;
}

// ====================测试代码====================
void Test(const char* testName, double base, int exponent, double expectedResult, bool expectedFlag)
{
    double result = Power(base, exponent);
    if (equal(result, expectedResult))
        std::cout << testName << " passed" << std::endl;
    else
        std::cout << testName << " FAILED" << std::endl;
}

int main(int argc, char* argv[])
{
    // 底数、指数都为正数
    Test("Test1", 2, 3, 8, false);

    // 底数为负数、指数为正数
    Test("Test2", -2, 3, -8, false);

    // 指数为负数
    Test("Test3", 2, -3, 0.125, false);

    // 指数为0
    Test("Test4", 2, 0, 1, false);

    // 底数、指数都为0
    Test("Test5", 0, 0, 0, false);

    // 底数为0、指数为正数
    Test("Test6", 0, 4, 0, false);

    // 底数为0、指数为负数
    Test("Test7", 0, -4, 0, true);

    return 0;
}
