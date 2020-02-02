// 3.4.2 思考题
// 题目2

#include <cstdio>
#include <cstring>

#define maxn 1000000 + 10

int main(int argc, char **argv)
{
    char s[maxn];
    scanf("%s", s);
    int tot = 0;
    size_t len = strlen(s);
    for (size_t i = 0; i < len; ++i)
    {
        if (s[i] == '1')
        {
            tot++;
        }
    }
    printf("%d\n", tot);
}