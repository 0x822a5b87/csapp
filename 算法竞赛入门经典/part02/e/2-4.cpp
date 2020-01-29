#include "iostream"
#include "ctime"

/*
 * 1. 对于只有加，减，乘 的整数表达式除以 n 的余数，可以每步计算之后都进行求余
 * 2. 在内层循环中进行了很多次重复的计算，我们可以优化这个重复的计算
 */

const int MOD = 1000000;

int main(int argc, char **argv)
{
    int num, S = 0;
    std::cin >> num;
    int      factorial = 1;
    for (int i         = 1; i <= num; ++i)
    {
//        int factorial = 1;
//        for (int j = 1; j <= i; ++j)
//        {
//            factorial = (factorial * j) % MOD;
//        }

        factorial = factorial * i % MOD;

        S = (S + factorial) % MOD;
    }

    printf("S = %d\n", S);
    printf("Time used = %.2f\n", (double) clock() / CLOCKS_PER_SEC);

    return 0;
}