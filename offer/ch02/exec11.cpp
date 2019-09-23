//
// Created by 杜航宇 on 2019-09-20.
//
// 输入一个递增排序的数组的一个旋转数组，输出旋转数组的最小元素
// 旋转数组是将一个数组的最开始的若干个元素搬运到数组的末尾
// 例如，数组 {1, 2, 3, 4, 5}，它的一个旋转数组是 {3, 4, 5, 1, 2}

#include "iostream"

// 思路就是，旋转之后的数组其实被划分为两个排序数组 {3, 4, 5} 和 {1, 2}
// 而且前面的子数组都大于后面的子数组的元素。

// 在排序的数组中，我们可以用二分查找法实现 O(log n) 的查找

// 我们使用两个指针，两个指针在最开始分别指向数组的第一个数字和最后一个数字
// 我们让指针在数组中移动，并且保持第一个指针指向第一个数组中的元素，第二个指针指向第二个数组中的元素
// 在经过若干次的移动之后，两个指针将会相邻，此时第二个指针就是我们指向的元素

// 有两种特殊情况
// 1. {0, 1, 1, 1, 1, 1}
// 这种在调换多个数字之后 {1, 0, 1, 1, 1, 1}
// 在循环的第一次之后可能会直接导致指针跳过最小值
// 2. {1, 2, 3, 4, 5}
// 这种初始指针就都在第一个数组中

int Min(int *numbers, int length)
{
    if (numbers == nullptr)
    {
        return 0;
    }
    int *first = numbers, *second = numbers + length - 1;
    while (first < second - 1)
    {
        int *mid = first + (second - first) / 2;
        if (*second > *mid)
        {
            // *second > *mid
            // 如果 *second > *mid。
            // 那么 mid 一定在第二个数组中
            // 反之，如果 *first < *mid
            // mid 不一定在第一个队列中，因为第一个队列的长度有可能为 0(在不移动任何数字的情况下)
            second = mid;
        }
        else if (*second == *mid)
        {
            // 当 *second == *mid 时， mid 有可能在第一个队列，也有可能在第二个队列
            // 我们对两个队列分别求 Min，并取最小值即可
            int min0 = Min(first, (mid - numbers));
            int min1 = Min(mid, (second - mid));

            return min0 > min1 ? min1 : min0;;
        }
        else
        {
            first = mid;
        }
    }

    // 对于第一个队列为空的，最后计算的结果是 *first > *second
    int value  = (*second > *first) ? *first : *second;
    return value;
}

// ==================== 测试代码 ====================
void Test(int *numbers, int length, int expected)
{
    int result = 0;
    try
    {
        result = Min(numbers, length);

        for (int i = 0; i < length; ++i)
            printf("%d ", numbers[i]);

        if (result == expected)
            printf("\tpassed\n");
        else
            printf("\tfailed\n");
    }
    catch (...)
    {
        if (numbers == nullptr)
            printf("Test passed.\n");
        else
            printf("Test failed.\n");
    }
}

int main(int argc, char *argv[])
{
    // 典型输入，单调升序的数组的一个旋转
    int array1[] = {3, 4, 5, 1, 2};
    Test(array1, sizeof(array1) / sizeof(int), 1);

    // 有重复数字，并且重复的数字刚好的最小的数字
    int array2[] = {3, 4, 5, 1, 1, 2};
    Test(array2, sizeof(array2) / sizeof(int), 1);

    // 有重复数字，但重复的数字不是第一个数字和最后一个数字
    int array3[] = {3, 4, 5, 1, 2, 2};
    Test(array3, sizeof(array3) / sizeof(int), 1);

    // 有重复的数字，并且重复的数字刚好是第一个数字和最后一个数字
    int array4[] = {1, 0, 1, 1, 1};
    Test(array4, sizeof(array4) / sizeof(int), 0);

    // 单调升序数组，旋转 0 个元素，也就是单调升序数组本身
    int array5[] = {1, 2, 3, 4, 5};
    Test(array5, sizeof(array5) / sizeof(int), 1);

    // 数组中只有一个数字
    int array6[] = {2};
    Test(array6, sizeof(array6) / sizeof(int), 2);

    // 输入 nullptr
    Test(nullptr, 0, 0);

    // 有重复的数字，并且重复的数字刚好是第一个数字和最后一个数字
    int array7[] = {1, 1, 1, 0, 1};
    Test(array7, sizeof(array7) / sizeof(int), 0);

    return 0;
}
