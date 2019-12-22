//
// Created by 杜航宇 on 2019-11-28.
//

#include <zconf.h>
#include "iostream"

int main()
{
    setenv("name", "hangyudu", 1);
    std::cout << getenv("name") << std::endl;

    unsetenv("name");
    char *name = getenv("name");
    std::cout << ((name == nullptr) ? "name is nullptr" : name) << std::endl;

    printf("main pid = [%d]\n", getpid());

    char * const argv[] = {"hello", "world"};
    execve("print", argv, nullptr);

    // 下面这段代码将不会运行
    printf("after running exeve: [%d]\n", getpid());
}
