// 0,1,…,n－1这n个数字排成一个圆圈，从数字0开始每次从这个圆圈里删除第m个数字。
// 求出这个圆圈里剩下的最后一个数字。
#include "vector"
#include "iostream"

int LastRemaining_Solution(int n, int m)
{
    std::vector<int> v;
    v.reserve(n);
    for (int i = 0; i < n; ++i)
        v.push_back(i);

    int current_position = 0;
    for (int count = n; count > 1; --count)
    {
        for (int i = 0; ; )
        {
            if (v[current_position] != -1)
            {
                ++i;
            }
            if (i >= m)
            {
                break;
            }
            ++current_position;
            if (current_position >= n)
            {
                current_position %= n;
            }
        }
        v[current_position] = -1;
    }

    for (int i = 0; i < n; ++i)
    {
        if (v[i] != -1)
        {
            return v[i];
        }
    }

    return -1;
}

int main(int argc, char **argv)
{
    std::cout << LastRemaining_Solution(5, 3) << std::endl;
}