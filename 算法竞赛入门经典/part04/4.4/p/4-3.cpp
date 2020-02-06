#include <vector>
#include "iostream"

// 4.4 例题 4-3
// UVa 133
// 有几个问题需要注意
// 1. 在循环计算 aIndex 和 bIndex 时，必须判断 cnt == k 和 cnt == m 来提前退出循环
// 否则会导致 aIndex 和 bIndex 多计算一次
// 2. bIndex 的类型是 unsigned，所以如果我们使用 if (bIndex < 0) 来修改 bIndex 的索引
// 将会发生异常
// 3. aIndex 和 bIndex 的计算可以抽象为一个函数，并使用一个参数步长来表示 ++ 或者 --

int main(int argc, char **argv)
{
    int n, k, m;
    std::cin >> n >> k >> m;
    std::vector<int> q;
    for (std::vector<int>::size_type i = 1; i <= n; ++i)
    {
        q.push_back(i);
    }

    int remaining = n;
    for (std::vector<int>::size_type aIndex = 0, bIndex = n - 1;
         remaining != 0;)
    {
        int cnt = 0;
        while(true)
        {
            if (q[aIndex] != 0)
                ++cnt;
            if (cnt == k)
                break;
            ++aIndex;
            if (aIndex >= n)
                aIndex %= n;
        }

        cnt = 0;
        while (true)
        {
            if (q[bIndex] != 0)
                ++cnt;
            if (cnt == m)
                break;

            if (bIndex == 0)
            {
                bIndex = n - 1;
            }
            else
                --bIndex;
        }

        if (aIndex != bIndex)
        {
            remaining -= 2;
            std::cout << q[aIndex] << " " << q[bIndex] << ",";
        }
        else
        {
            --remaining;
            std::cout << q[aIndex] << ",";
        }
        q[aIndex] = 0;
        q[bIndex] = 0;
    }

    return 0;
}
