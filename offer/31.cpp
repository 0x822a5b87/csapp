// 在古老的一维模式识别中，常常需要计算连续子向量的最大和，当向量全为正数的时候，问题很好解决。
// 例如:{6,-3,-2,7,-15,1,2,2}, 连续子向量的最大和为 8 (从第 0 个开始，到第 3 个为止)。 你会不会被他忽悠住？
#include "iostream"
#include "vector"

// 动态规划
// 1. 假设数组 arr[i] 表示的是以 i 结尾的连续子向量的最大和
// 简单的来讲，我们可以使用递归来解决说明这个问题
// f(i) = max(f(i-1) + src[i], src[i])

// 贪心算法
int FindGreatestSumOfSubArray(const std::vector<int>& array)
{
    if (array.empty())
    {
        return 0;
    }

    int maxSum = array[0];
    int sum = 0;
    for (const auto &num : array)
    {
        sum += num;
        if (sum > maxSum)
        {
            maxSum = sum;
        }
        if (sum < 0)
        {
            sum = 0;
        }
    }
    return maxSum;
}

int main(int argc, char **argv)
{
//    std::vector<int> v{6, -3, -2, 7, -15, 1, 2, 2};
    std::vector<int> v{-1, -2, -3};
    std::cout << FindGreatestSumOfSubArray(v) << std::endl;
}