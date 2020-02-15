// 输入一个递增排序的数组和一个数字s，在数组中查找两个数，使得它们的和正好是s。
// 如果有多对数字的和等于s，输出任意一对即可。
#include "vector"
#include "iostream"

int sumToSelf(int n)
{
    int sum = 0;
    for (int i = 1; i < n; ++i)
    {
        sum += i;
    }
    return sum;
}

std::vector<std::vector<int> > FindContinuousSequence(int sum)
{
    std::vector<std::vector<int>> sumArr;

    for (int start = sum / 2, sumOfCnt = 2;
         sumOfCnt * (sumOfCnt - 1) <= 2 * sum;
         ++sumOfCnt)
    {
        int x = (sum - sumToSelf(sumOfCnt) - start * sumOfCnt) / sumOfCnt;
        int tmpSum = 0;
        for (int i = 0; i < sumOfCnt; ++i)
        {
            tmpSum += (start + i + x);
        }
        if (tmpSum == sum && (start + x) != 0)
        {
            start = start + x;
            std::vector<int> v;
            v.reserve(sumOfCnt);
            for (int i = 0; i < sumOfCnt; ++i)
            {
                v.push_back(start + i);
            }
            sumArr.push_back(v);
        }
    }

    std::reverse(std::begin(sumArr), std::end(sumArr));

    return sumArr;
}

int main(int argc, char **argv)
{
    const std::vector<std::vector<int>> &v = FindContinuousSequence(3);
    for (const auto &vi : v)
    {
        for (const auto &num : vi)
        {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }
}
