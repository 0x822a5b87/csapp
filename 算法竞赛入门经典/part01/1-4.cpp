#include "cstdio"

int main(int argc, char **argv)
{
    int m, n;
    scanf("%d %d", &m, &n);
    int x, y;
    y = (n - 2 * m) / 2;
    x = m - y;

    if ((x + y == m)
        && (2 * x + 4 * y == n))
    {
        printf("%d %d", x, y);
    }
    else
    {
        printf("No answer");
    }
}