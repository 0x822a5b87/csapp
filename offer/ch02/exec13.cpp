//
// Created by 杜航宇 on 2019-09-23.
//

#include <deque>
#include "iostream"

// 一个格子能否到达需要满足两个条件
// 1. 格子的坐标的数位之和大于 k
// 2. 格子能够通过上、下、左、右移动到达
// 思路是，我们从 (0, 0) 出发，每次都标记一个点所有能到达的位置，当这个点能到达的位置是一个新的点时，我们就将这个点加入到一个
// 列表中。
// 当我们整个列表中所有的元素都被消耗完毕的时候，我们就得到了整个地图上所有能到达的点。

// 这是一个比较典型的不动点算法

void printRet(bool *reachable, int m, int n)
{
    for (int i = 0; i != m; ++i)
    {
        for (int j = 0; j != n; ++j)
        {
            std::cout << reachable[i * n + j] << " ";
        }
        std::cout << std::endl;
    }
}

int countDigit(int num)
{
    int count = 0;
    while (num > 0)
    {
        count += num % 10;
        num /= 10;
    }
    return count;
}

void addPoints(std::deque<int> &points, int row, int col, int m, int n)
{
    if (row < m && row >= 0 && col < n && col >= 0)
    {
        int index = row * n + col;
        points.push_back(index);
    }
}

void updateAround(int threshold, std::deque<int> &points, bool *reachable, int index, int m, int n)
{
    int col = index % n;
    int row = (index - col) / n;

    const int up   = row - 1, down = row + 1,
              left = col - 1, right = col + 1;

    if (countDigit(row) + countDigit(col) <= threshold)
    {
        reachable[row * n + col] = true;
        addPoints(points, row, col, m, n);
        addPoints(points, up, col, m, n);
        addPoints(points, down, col, m, n);
        addPoints(points, row, left, m, n);
        addPoints(points, row, right, m, n);
    }
}

void checkPointReachable(int threshold, std::deque<int> &points, bool *reachable, int m, int n)
{
    if (points.empty())
    {
        return;
    }
    const int &index = points.front();
    points.pop_front();
    if (!reachable[index])
    {
        updateAround(threshold, points, reachable, index, m, n);
    }

    checkPointReachable(threshold, points, reachable, m, n);
}

int checkPointDigit(const bool *reachable, int m, int n, int threshold)
{
    int count = 0;

    for (int i = 0; i != m * n; ++i)
    {
        if (!reachable[i])
        {
            continue;
        }

        int col = i % n;
        int row = (i - col) / m;

        if (countDigit(row) + countDigit(col) > threshold)
        {
            continue;
        }

        ++count;
    }
    return count;
}

int movingCount(int threshold, int m, int n)
{
    std::deque<int> points = {0};
    bool            reachable[m * n];

    for (int i = 0; i != m * n; ++i)
    {
        reachable[i] = false;
    }
    checkPointReachable(threshold, points, reachable, m, n);

    return checkPointDigit(reachable, m, n, threshold);
}

// 错误的算法，因为在部分情况下有的格子是无法到达的

// 我们可以直接对 1 行和 1 列的情况做特殊处理，不过这样不是我们这道题的本意


//int movingNormal(int threshold, int rows, int cols)
//{
//    int count = 0;
//    for (int i = 0; i != rows; ++i)
//    {
//        for (int j = 0; j != cols; ++j)
//        {
//            if ((countDigit(i) + countDigit(j)) <= threshold)
//            {
//                ++count;
//            }
//        }
//    }
//    return count;
//}
//
//int movingOneRowOrCol(int threshold, int rowOrCol)
//{
//    int count = 0;
//    for (int i = 0; i < rowOrCol; ++i)
//    {
//        if (countDigit(i) <= threshold)
//        {
//            ++count;
//        }
//        else
//        {
//            break;
//        }
//    }
//    return count;
//}
//
//int movingCount(int threshold, int rows, int cols)
//{
//    if (threshold < 0 || rows <= 0 || cols <= 0)
//    {
//        return 0;
//    }
//
//    if (rows == 1)
//    {
//        return movingOneRowOrCol(threshold, cols);
//    }
//
//    if (cols == 1)
//    {
//        return movingOneRowOrCol(threshold, rows);
//    }
//
//    return movingNormal(threshold, rows, cols);
//}

// ====================测试代码====================
void test(char *testName, int threshold, int rows, int cols, int expected)
{
    if (testName != nullptr)
        printf("%s begins: ", testName);

    if (movingCount(threshold, rows, cols) == expected)
        printf("Passed.\n");
    else
        printf("FAILED.\n");
}

// 方格多行多列
void test1()
{
    test("Test1", 5, 10, 10, 21);
}

// 方格多行多列
void test2()
{
    test("Test2", 15, 20, 20, 359);
}

// 方格只有一行，机器人只能到达部分方格
void test3()
{
    test("Test3", 10, 1, 100, 29);
}

// 方格只有一行，机器人能到达所有方格
void test4()
{
    test("Test4", 10, 1, 10, 10);
}

// 方格只有一列，机器人只能到达部分方格
void test5()
{
    test("Test5", 15, 100, 1, 79);
}

// 方格只有一列，机器人能到达所有方格
void test6()
{
    test("Test6", 15, 10, 1, 10);
}

// 方格只有一行一列
void test7()
{
    test("Test7", 15, 1, 1, 1);
}

// 方格只有一行一列
void test8()
{
    test("Test8", 0, 1, 1, 1);
}

// 机器人不能进入任意一个方格
void test9()
{
    test("Test9", -10, 10, 10, 0);
}

int main(int agrc, char *argv[])
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

    return 0;
}
