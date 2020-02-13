// 在数组中的两个数字如果前面一个数字大于后面的数字，则这两个数字组成一个逆序对。
// 输入一个数组，求出这个数组中的逆序对的总数。
// 例如在数组{7,5,6,4}中，一共存在5个逆序对，分别是（7,6）、（7,5）、（7,4）、（6,4）和（5,4）。
#include "vector"

using namespace std;

class Solution
{
public:
    int InversePairs(vector<int> data)
    {
        if (data.size() == 0)
        {
            return 0;
        }
        // 排序的辅助数组
        vector<int> copy;
        for (int    i : data)
        {
            copy.push_back(i);
        }
        return InversePairsCore(data, copy,
                                0, data.size() - 1)
               % 1000000007;
    }

    long InversePairsCore(vector<int> &data, vector<int> &copy, int begin, int end)
    {
        // 如果指向相同位置，则没有逆序对。
        if (begin == end)
        {
            copy[begin] = data[end];
            return 0;
        }
        // 求中点
        int  mid        = (end + begin) >> 1;
        // 使 data 左半段有序，并返回左半段逆序对的数目
        long leftCount  = InversePairsCore(copy, data, begin, mid);
        // 使 data 右半段有序，并返回右半段逆序对的数目
        long rightCount = InversePairsCore(copy, data, mid + 1, end);

        int  i         = mid; //i 初始化为前半段最后一个数字的下标
        int  j         = end; //j 初始化为后半段最后一个数字的下标
        int  indexcopy = end; // 辅助数组复制的数组的最后一个数字的下标
        long count     = 0; // 计数，逆序对的个数，注意类型

        while (i >= begin && j >= mid + 1)
        {
            if (data[i] > data[j])
            {
                copy[indexcopy--] = data[i--];
                count += j - mid;
            }
            else
            {
                copy[indexcopy--] = data[j--];
            }
        }
        for (; i >= begin; --i)
        {
            copy[indexcopy--] = data[i];
        }
        for (; j >= mid + 1; --j)
        {
            copy[indexcopy--] = data[j];
        }
        return leftCount + rightCount + count;
    }
};
