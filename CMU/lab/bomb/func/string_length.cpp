//
// Created by 杜航宇 on 2019-08-16.
//

#include "iostream"

size_t string_length(char *ptr)
{
    if (ptr == nullptr) {
        return 0u;
    }
    int len = 0u;
    while (ptr != nullptr)
    {
        ++len;
        ++ptr;
    }
    return len;
}

size_t string_length2(char *ptr)
{
    if (ptr == nullptr)
    {
        return 0u;
    }
    char *tmp = ptr;
    while (*tmp != '\0')
    {
        ++tmp;
    }
    return tmp - ptr;
}

int main()
{
    char *ptr = "hello";

    std::cout << string_length2(ptr) << std::endl;
}
