//
// Created by 杜航宇 on 2019-09-24.
//
// 面试题14：剪绳子
// 给一根长度为 n 的绳子，把绳子剪成 m 段，求剪断的绳子的最大乘积是多少

#include "iostream"

//==============================================================================================================================
//==============================================================================================================================
//==============================================================================================================================
// 这里是我们错误的思路
//
//
// 使用动态规划，时间复杂度 O(n2) 空间复杂度 O(n)
// 整个的思路是：
// 1. 第一步我们把绳子剪成两段，假设两段的长度分别为 a 和 b，那么 a * b 应该是剪成两段的选择中最长的；
// 2. 假设 a != 1 && b != 1，那么我们对 a 和 b 继续递归调用直到绳子不能再继续被剪短
//==============================================================================================================================
//==============================================================================================================================
//==============================================================================================================================



//==============================================================================================================================
// 正确的思路是：假设我们现在的绳子被剪断成 k[0], k[1], ..., k[m]
// 如果我们将 k[0] 看成一部分，其余的看成另一部分，那么我们就将问题拆分成了
// f(n) = max(k[0] * f(n-k[0]))
// 而我们在上面的思路错的地方在于我们求的是 max(k[0] * (n-k[0]))
// 但是如同我们斐波那契数列，下面的这个解法性能相当差，对于 test11 已经完全无法正常计算
//==============================================================================================================================

int doProductAfterCutting(int length, int cache[length])
{
    if (cache[length - 1])
    {
        return cache[length - 1];
    }

    int maxProductOfTwoSegment = length;
    int maxLeft = 1, maxRight = length - maxLeft;

    for (int left = 1, right = length - left;
         left < length && right > 0;
         ++left, right = length - left)
    {
        int curProductOfTwoSegment = left * doProductAfterCutting(right, cache);

        if (curProductOfTwoSegment > maxProductOfTwoSegment)
        {
            maxProductOfTwoSegment = curProductOfTwoSegment;
            maxLeft = left;
            maxRight = right;
        }
    }

    if (maxLeft == 1 || maxRight == 1)
    {
        cache[length - 1] = maxProductOfTwoSegment;
        return maxProductOfTwoSegment;
    }
    else
    {
        return doProductAfterCutting(maxLeft, cache) * doProductAfterCutting(maxRight, cache);
    }
}

int maxProductAfterCutting_solution3(int length)
{
    if (length <= 1)
    {
        return 0;
    }

    if (length == 2)
    {
        return 1;
    }

    if (length == 3)
    {
        return 2;
    }

    int arr[length];
    for (int i = 0; i != length; ++i)
    {
        arr[i] = 0;
    }

    return doProductAfterCutting(length, arr);
}

//==============================================================================================================================
//==============================================================================================================================
//==============================================================================================================================
// 这个是优化的方法，我们的 f(n) 可以等于 max((1 * f(n-1)), (2 * f(n - 2)), ..., ((n - 1) * f(1)))
// 但是在之前的步骤中，我们在递归的过程中多次的计算了 f(x) 的值，并且由于深层的递归，我们的速度非常慢
// 所以我们换了个思路，在 cache 中存放了 length 的对应的 f(n)。值得注意的是，这里存放的 cache[1] != f(1)
// 因为 f(1) 无法剪断，所以返回0，而这里的 cache[1] 存放的是已经分解的数字，它是作为乘法中的一个因子出现的
//==============================================================================================================================
//==============================================================================================================================
//==============================================================================================================================
int maxProductAfterCutting_solution1(int length)
{
    if (length <= 1)
    {
        return 0;
    }

    if (length == 2)
    {
        return 1;
    }

    if (length == 3)
    {
        return 2;
    }

    int cache[length + 1];
    cache[1] = 1;
    cache[2] = 2;
    cache[3] = 3;
    for (int i = 4; i <= length; ++i)
    {
        int max = 0;
        for (int j = 1; j < i; ++j)
        {
            int value = j * cache[i - j];
            if (value > max)
            {
                max = value;
            }
        }
        cache[i] = max;
    }

    return cache[length];
}

int maxProductAfterCutting_solution2(int length)
{
    return 0;
}

// ====================测试代码====================
void test(const char* testName, int length, int expected)
{
    int result1 = maxProductAfterCutting_solution1(length);
    if(result1 == expected)
        std::cout << "Solution1 for " << testName << " passed." << std::endl;
    else
        std::cout << "Solution1 for " << testName << " FAILED." << std::endl;

//    int result2 = maxProductAfterCutting_solution2(length);
//    if(result2 == expected)
//        std::cout << "Solution2 for " << testName << " passed." << std::endl;
//    else
//        std::cout << "Solution2 for " << testName << " FAILED." << std::endl;
}

void test1()
{
    int length = 1;
    int expected = 0;
    test("test1", length, expected);
}

void test2()
{
    int length = 2;
    int expected = 1;
    test("test2", length, expected);
}

void test3()
{
    int length = 3;
    int expected = 2;
    test("test3", length, expected);
}

void test4()
{
    int length = 4;
    int expected = 4;
    test("test4", length, expected);
}

void test5()
{
    int length = 5;
    int expected = 6;
    test("test5", length, expected);
}

void test6()
{
    int length = 6;
    int expected = 9;
    test("test6", length, expected);
}

void test7()
{
    int length = 7;
    int expected = 12;
    test("test7", length, expected);
}

void test8()
{
    int length = 8;
    int expected = 18;
    test("test8", length, expected);
}

void test9()
{
    int length = 9;
    int expected = 27;
    test("test9", length, expected);
}

void test10()
{
    int length = 10;
    int expected = 36;
    test("test10", length, expected);
}

void test11()
{
    int length = 50;
    int expected = 86093442;
    test("test11", length, expected);
}

int main(int agrc, char* argv[])
{
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
    test9();
    test10();
    test11();

    return 0;
}