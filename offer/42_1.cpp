// 字符串的左旋转操作是把字符串前面的若干个字符转移到字符串的尾部。
// 请定义一个函数实现字符串左旋转操作的功能。
// 比如输入字符串"abcdefg"和数字2，该函数将返回左旋转2位得到的结果"cdefgab"。
// cdefgba
#include "string"
#include "iostream"

std::string RotateRecursive(std::string &str, int n, int head)
{
    if (n <= 0 || n >= str.size())
    {
        return str;
    }

    int rotate = 0;
    size_t i;
    for (i = head; i + n < str.size(); ++i)
    {
        ++rotate;
        std::swap(str[i], str[i + n]);
    }

    if (rotate % n != 0)
    {
        int remainingRotate = n - (rotate % n);
        return RotateRecursive(str, remainingRotate, i);
    }
    else
    {
        return str;
    }
}


std::string Rotate(std::string &str, int n, int head)
{
    if (n <= 0 || n >= str.size())
    {
        return str;
    }

    // 下面的这个 while 循环等同于前面的递归
    // 1. 退出递归条件和退出循环条件是一样的，都是 rotate == 0
    // 2. 递归调用的参数，要么作为全局变量保存，要么每次都重新计算
    int rotate = 0;
    do
    {
        int remainingRotate = n - (rotate % n);
        n = remainingRotate;
        rotate = 0;

        for (; head + n < str.size(); ++head)
        {
            ++rotate;
            std::swap(str[head], str[head + n]);
        }
    }
    while(rotate % n != 0);

    return str;
}

std::string LeftRotateString(std::string str, int n)
{
    Rotate(str, n, 0);

    return str;
}

int main(int argc, char **argv)
{
    std::cout << LeftRotateString("abcdefg", 1) << std::endl;
    std::cout << LeftRotateString("abcdefg", 2) << std::endl;
    std::cout << LeftRotateString("abcdefg", 3) << std::endl;
    std::cout << LeftRotateString("abcdefg", 4) << std::endl;
    std::cout << LeftRotateString("abcdefg", 5) << std::endl;
    std::cout << LeftRotateString("abcdefg", 6) << std::endl;
}