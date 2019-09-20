//
// Created by 杜航宇 on 2019-09-19.
//
// 青蛙跳台阶问题
// 青蛙可以跳1级或者2级台阶。求青蛙跳上一个 n 级台阶的总跳法

#include "iostream"

// 青蛙跳 n 级台阶可以的总跳法可以转变为
// (跳 n-1 级台阶的跳法) + (跳 n-2 级台阶的跳法) + 1
int jumpRec(unsigned n)
{
    if (n <= 0)
    {
        return 0;
    }
    if (n == 1)
    {
        return 1;
    }
    if (n == 2)
    {
        return 2;
    }

    return jumpRec(n - 1) + jumpRec(n - 2);
}

unsigned jump(unsigned n)
{
    if (n <= 0)
    {
        return 0;
    }
    if (n == 1)
    {
        return 1;
    }
    if (n == 2)
    {
        return 2;
    }

    unsigned result       = 0;
    unsigned jumpMinusOne = 1, jumpMinusTwo = 2;

    for (int i = 3; i <= n; ++i)
    {
        result = jumpMinusOne + jumpMinusTwo;
        unsigned tmp = jumpMinusTwo;
        jumpMinusTwo += jumpMinusOne;
        jumpMinusOne = tmp;
    }

    return result;
}

int main()
{
    assert(jumpRec(0) == 0);
    assert(jumpRec(1) == 1);
    assert(jumpRec(2) == 2);
    assert(jumpRec(3) == 3);
    assert(jumpRec(4) == 5);
    assert(jumpRec(5) == 8);

    assert(jumpRec(0) == jump(0));
    assert(jumpRec(1) == jump(1));
    assert(jumpRec(2) == jump(2));
    assert(jumpRec(3) == jump(3));
    assert(jumpRec(4) == jump(4));
    assert(jumpRec(5) == jump(5));
    assert(jumpRec(10) == jump(10));
}
