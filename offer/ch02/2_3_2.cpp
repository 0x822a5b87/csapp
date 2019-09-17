//
// Created by 杜航宇 on 2019-09-16.
//

#include "iostream"

int main()
{
    char str1[] = "hello world";
    char str2[] = "hello world";

    const char *str3 = "hello world";
    const char *str4 = "hello world";

    // str1 和 str2 是数组，所以他们会拥有独立的空间
    if (str1 == str2)
    {
        std::cout << "str1 and str2 are same." << std::endl;
    }
    else
    {
        std::cout << "str1 and str2 are not same." << std::endl;
    }

    // str3 和 str4 他们是两个指针，他们指向同一个对象
    if (str3 == str4)
    {
        std::cout << "str3 and str4 are same." << std::endl;
    }
    else
    {
        std::cout << "str3 and str4 are not same." << std::endl;
    }
}
