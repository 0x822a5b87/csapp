// 题目：
//
// 我们把只包含因子2、3和5的数称作丑数（Ugly Number）。
// 求按从小到大的顺序的第1500个丑数。例如6、8都是丑数，但14不是，因为它包含因子7。习惯上我们把1当做第一个丑数。

// 采用时间换空间的策略，每一个丑数肯定是由另外一个丑数 M
// M * 2 或者 M * 3 或者 M * 5 得到的
// 我们可以将得到的丑数顺序排列，我们每次都去生成下一个新的丑数。
// 假设我们当前的最大丑数为 Max，那么必然存在
// A[x] * 2 > Max 或者 A[y] * 3 > Max 或者 A[z] * 5 > Max
// 每个数字 A[i] 可以通过 A[i] * 2, A[i] * 3, A[i] * 5 生成三个新的丑数
// 我们可以维持三个不同的索引，indexOf2，indexOf3，indexOf5
// 每次我们计算新的丑数的时候去 min(arr[indexOf2] * 2, arr[indexOf3] * 3, arr[indexOf5] * 5)
#include "vector"
#include "iostream"

int GetUglyNumber_Solution(int index)
{
    int res = 0;
    std::vector<int> uglyNumbers{1};
    std::vector<int >::size_type indexOf2 = 0, indexOf3 = 0, indexOf5 = 0;
    for (int i = 0; i < index; ++i)
    {
        res = uglyNumbers[i];
        while (uglyNumbers[indexOf2] * 2 <= res)
            indexOf2++;
        while (uglyNumbers[indexOf3] * 3 <= res)
            indexOf3++;
        while (uglyNumbers[indexOf5] * 5 <= res)
            indexOf5++;
        int productBy2 = uglyNumbers[indexOf2] * 2;
        int productBy3 = uglyNumbers[indexOf3] * 3;
        int productBy5 = uglyNumbers[indexOf5] * 5;
        int nextUgly   = std::min(std::min(productBy2, productBy3), productBy5);
        uglyNumbers.push_back(nextUgly);
    }

    return res;
}

int main(int argc, char **argv)
{
    for (int i = 1; i < 20; ++i)
    {
        std::cout << GetUglyNumber_Solution(i) << " ";
    }
    std::cout << std::endl;
}
