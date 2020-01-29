#include <cmath>
#include "iostream"

void print_aabb()
{
    for (int i = 1; i <= 9; ++i)
    {
        for (int j = 0; j <= 9; ++j)
        {
            // 获得所有形如 AABB 的数字
            int n = 1100 * i + 11 * j;
            int sq = floor(sqrt(n) + 0.5);
            if (sq * sq == n)
            {
                printf("%d %d\n", n, sq);
            }
        }
    }
}

int main(int argc, char **argv)
{
    print_aabb();
}
