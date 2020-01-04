#include "../apue.h"

int main(int argc, char **argv)
{
    char *hp = getenv("SHELL");
    printf("%s\n", hp);
    // /bin/zsh

    if (setenv("SHELL", "/bin/bash", 0) != 0)
        err_sys("setenv SHELL failed");
    hp = getenv("SHELL");
    printf("%s\n", hp);
    // /bin/zsh

    if (setenv("SHELL", "/bin/bash", 1) != 0)
        err_sys("setenv SHELL failed");
    hp = getenv("SHELL");
    printf("%s\n", hp);
    // /bin/bash

    const char *ep  = "Test_env=test_env_value";
    const char *ep2 = "Test_env=another_test_env_value";
    char       mutable_env[MAXLINE];
    strcpy(mutable_env, ep);
    if (putenv(mutable_env) != 0)
        err_sys("failed putenv");

    hp = getenv("Test_env");
    printf("Test_env = %s\n", hp);
    // Test_env = test_env_value
    printf("edit Test_env\n");
    strcpy(mutable_env, ep2);
    hp = getenv("Test_env");
    printf("Test_env = %s\n", hp);
    // Test_env = another_test_env_value

    const char *ep3 = "setenv";
    const char *ep4 = "another setenv";
    strcpy(mutable_env, ep3);
    setenv("Another_test_env", mutable_env, 1);
    hp = getenv("Another_test_env");
    printf("Another_test_env = %s\n", hp);
    // Another_test_env = setenv
    strcpy(mutable_env, ep4);
    hp = getenv("Another_test_env");
    printf("Another_test_env = %s\n", hp);
    // Another_test_env = setenv
}