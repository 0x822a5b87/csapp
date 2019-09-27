//
// Created by 杜航宇 on 2019-09-27.
//
// 判断字符串是否表示数字。
// +100、5e2、-123、3.1416、-1E-16 是数字
// 12e、1a3.14、+-5、12e+5.4 不是数字
//
// 可以用正则表达式来表示数字
//

#include "iostream"

bool readSymbol(const char **str)
{
    if (**str == '+' || **str == '-')
    {
        *str = *str + 1;
        return true;
    }
    else
    {
        return false;
    }
}

bool readNaturalNumber(const char **str)
{
    if (!isdigit(**str))
    {
        return false;
    }

    while (isdigit(**str))
    {
        ++*str;
    }

    return true;
}

//    Test("Test20", "", false);
bool isNumeric(const char *str)
{
    if (str == nullptr || *str == '\0')
    {
        return false;
    }

    // 读取符号
    readSymbol(&str);
    // 读取自然数
    bool numeric = readNaturalNumber(&str);

    // 如果后面紧跟一个 . ，那么我们继续扫描下一个自然数。
    if (*str == '.')
    {
        // 读取紧跟在 . 之后的自然数
        bool numericAfter = readNaturalNumber(&++str);
        // 小数点的前后不能同时为空。但是 . 之前和之后有一个可以省略
        if (!numeric && !numericAfter)
        {
            return false;
        }
    }

    // 读取数字的平方部分
    if (*str == 'e' || *str == 'E')
    {
        if (!numeric)
        {
            return false;
        }
        readSymbol(&++str);
        numeric = readNaturalNumber(&str);
        if (!numeric)
        {
            return false;
        }
    }

    return *str == '\0';
}

// ====================测试代码====================
void Test(const char* testName, const char* str, bool expected)
{
    if(testName != nullptr)
        printf("%s begins: ", testName);

    if(isNumeric(str) == expected)
        printf("Passed.\n");
    else
        printf("FAILED.\n");
}


int main(int argc, char* argv[])
{
    Test("Test1", "100", true);
    Test("Test2", "123.45e+6", true);
    Test("Test3", "+500", true);
    Test("Test4", "5e2", true);
    Test("Test5", "3.1416", true);
    Test("Test6", "600.", true);
    Test("Test7", "-.123", true);
    Test("Test8", "-1E-16", true);
    Test("Test9", "1.79769313486232E+308", true);

    printf("\n\n");

    Test("Test10", "12e", false);
    Test("Test11", "1a3.14", false);
    Test("Test12", "1+23", false);
    Test("Test13", "1.2.3", false);
    Test("Test14", "+-5", false);
    Test("Test15", "12e+5.4", false);
    Test("Test16", ".", false);
    Test("Test17", ".e1", false);
    Test("Test18", "e1", false);
    Test("Test19", "+.", false);
    Test("Test20", "", false);
    Test("Test21", nullptr, false);

    return 0;
}
