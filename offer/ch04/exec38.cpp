//
// Created by 杜航宇 on 2019-10-04.
//
// 输入一个字符串，打印出改字符串中字符的所有排列

#include "iostream"

/*
 * 我们可以把这个问题分解为多个小问题：我们可以把一个字符串看做是由两个部分组成。
 * 第一个部分是它的第一个字符，第二个部分是它后续的字符。
 *
 * 整个计算分为两步：
 * 1. 求所有可能出现在第一个位置的字符，即把第一个字符和后面所有的字符交换
 * 2. 第二步固定第一个字符，求后面所有字符的排列
 *
 * 在我们的函数中，str 始终指向同一个字符串，我们通过移动 begin 来修改这个 str。
 * 当 begin == '\0' 时我们已经修改完了整个字符串
 */
void Permutation(char str[], char begin[])
{
    if (*begin == '\0')
    {
        std::cout << str << std::endl;
        return;
    }

    // 每一次循环，我们都以某一个字符作为第一个字符，并在循环结束的时候将它换回来
    for (char *ch = begin; *ch != '\0'; ++ch)
    {
        std::swap(*ch, *begin);
        // 我们现在已经以某一个字符作为首字符，随后我们只需要以后续的字符来做全排列即可
        Permutation(str, begin + 1);
        std::swap(*ch, *begin);
    }
}

void Permutation(char *str)
{
    if (str == nullptr)
    {
        return;
    }

    Permutation(str, str);
}

int main()
{
    char str[] = {'a', 'b', '\0'};
    Permutation(str);
}
