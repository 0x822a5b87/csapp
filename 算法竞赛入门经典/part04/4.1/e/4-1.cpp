#include "iostream"

// 1. 及时最终答案在所选择的数据类型范围内，计算的中间结果仍然可能溢出
// 2. 避免中间结果溢出的方法是进行 "约分"

long long factorial(int n)
{
    long long m =  1;
    for (int i = 1; i <= n; ++i)
    {
        m *= i;
    }

    return m;
}

long long C(int n, int m)
{
    return factorial(n) / (factorial(m) * factorial(n - m));
}

// n!/m!  = (m+1) * (m+2) * ... * n
// (n-m)! = 1 * 2 * ... * (n - m)
// 如果 m < n - m，那么 [m+1, n-m] 这个区间内的就是重复的
// 所以计算的时候可以计算
// [1, m]   和 [n-m+1, n] 这两个区间的数据
// 正常情况是计算
// [1, n-m] 和 [m+1, n]
// 对比一下就知道，当 m < n - m 时，可以通过替换 m = n - m 来减少计算量
long long C2(int n, int m)
{
    if (m < n - m)
        m = n - m;
    long long ans = 1;
    for (int i = m + 1; i <= n; i++)
        ans *= i;
    for (int i = 1; i <= n - m; i++)
        ans /= i;
    return ans;
}

int main(int argc, char **argv)
{
    std::cout << C(21, 1) << std::endl;
}