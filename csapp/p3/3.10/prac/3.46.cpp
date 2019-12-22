//
// Created by 杜航宇 on 2019-08-13.
//

#include "iostream"

char *get_line()
{
    char buf[4];
    char *result;
    gets(buf);
    result = static_cast<char *>(malloc(strlen(buf)));
    strcpy(result, buf);

    return result;
}

int main()
{
    std::cout << get_line() << std::endl;
}
