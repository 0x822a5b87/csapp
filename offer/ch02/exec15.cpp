//
// Created by 杜航宇 on 2019-09-25.
//

#include "iostream"

int NumberOf1(int n)
{
    int tool = 0x1;
    int count = 0;

    do
    {
        if (tool & n)
        {
            ++count;
        }
        tool <<= 1;
    } while (tool != 0x1 && tool != 0x0);

    return count;
}

// n - 1 的作用是
// <1> 对于末尾为 1 的数字简单的去掉 1
// <2> 对于末尾为 0 的数字，从左往右找到第一个为 1 的数字，将这个数字设置为 0，低位的全部设置为 1
// 随后 n & (n - 1)
// <1> 对于末尾为 1 或 0 的数字都是去掉最低位的 1
int NumberOf1_solution2(int n)
{
    int count = 0;

    while (n)
    {
        ++count;
        n &= (n - 1);
    }

    return count;
}

// ====================测试代码====================
void Test(int number, unsigned int expected)
{
    int actual = NumberOf1(number);
    if (actual == expected)
        printf("Solution1: Test for %p passed.\n", number);
    else
        printf("Solution1: Test for %p failed.\n", number);
}

int main(int argc, char* argv[])
{
    // 输入0，期待的输出是0
    Test(0, 0);

    // 输入1，期待的输出是1
    Test(1, 1);

    // 输入10，期待的输出是2
    Test(10, 2);

    // 输入0x7FFFFFFF，期待的输出是31
    Test(0x7FFFFFFF, 31);

    // 输入0xFFFFFFFF（负数），期待的输出是32
    Test(0xFFFFFFFF, 32);

    // 输入0x80000000（负数），期待的输出是1
    Test(0x80000000, 1);

    return 0;
}
