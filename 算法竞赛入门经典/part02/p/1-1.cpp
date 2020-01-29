#include "iostream"

// 输入 100~999 中的所有水仙花数。
// A^3 + B^3 + C^3 = ABC

int main(int argc, char **argv)
{
    for (int num = 100; num <= 999; ++num)
    {
        int sum = 0, tmp = num;
        while (tmp > 0)
        {
            int lower = tmp % 10;
            sum += lower * lower * lower;
            tmp /= 10;
        }
        if (sum == num)
        {
            printf("%d\n", num);
        }
    }

    return 0;
}