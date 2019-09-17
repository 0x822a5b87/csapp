//
// Created by 杜航宇 on 2019-09-16.
//

#include "iostream"

/**
 * 如果我们从二维数组的中间去选取一个数字来和要查找的数字进行对比，那么下一次要查找的将是两个相互重叠的区域。
 * 如果 number > current，那么下次需要查找的将是左边和上边
 * 如果 number < current，那么下次需要查找的将是右边和下边
 * 而需要查找的区域将会重叠。
 *
 * 我们可以通过每次来查找数组的右上角来避免这个问题
 * 如果 number > current，那么下一次需要查找的将是当前列的下边部分
 * 如果 number < current，那么下次一需要查找的将是当前列的左边部分
 *
 * 这两个区域是不重叠的
 */
bool find_num(int *matrix, int rows, int columns, int number)
{
    bool found = false;
    if (matrix != nullptr && rows > 0 && columns > 0)
    {
        int curRow = 0, curCol = columns - 1;
        while (curRow < rows && curCol >= 0)
        {
            int upperRightCorner = matrix[curRow * columns + curCol];
            if (number > upperRightCorner)
            {
                ++curRow;
            }
            else if (number < upperRightCorner)
            {
                --curCol;
            }
            else
            {
                found = true;
                break;
            }
        }
    }
    return found;
}

// ==================== 测试代码 ====================
void Test(char *testName, int *matrix, int rows, int columns, int number, bool expected)
{
    if (testName != nullptr)
        printf("%s begins: ", testName);

    bool result = find_num(matrix, rows, columns, number);
    if (result == expected)
        printf("Passed.\n");
    else
        printf("Failed.\n");
}

//  1   2   8   9
//  2   4   9   12
//  4   7   10  13
//  6   8   11  15
// 要查找的数在数组中
void Test1()
{
    int matrix[][4] = {{1, 2, 8,  9},
                       {2, 4, 9,  12},
                       {4, 7, 10, 13},
                       {6, 8, 11, 15}};
    Test("Test1", (int *) matrix, 4, 4, 7, true);
}

//  1   2   8   9
//  2   4   9   12
//  4   7   10  13
//  6   8   11  15
// 要查找的数不在数组中
void Test2()
{
    int matrix[][4] = {{1, 2, 8,  9},
                       {2, 4, 9,  12},
                       {4, 7, 10, 13},
                       {6, 8, 11, 15}};
    Test("Test2", (int *) matrix, 4, 4, 5, false);
}

//  1   2   8   9
//  2   4   9   12
//  4   7   10  13
//  6   8   11  15
// 要查找的数是数组中最小的数字
void Test3()
{
    int matrix[][4] = {{1, 2, 8,  9},
                       {2, 4, 9,  12},
                       {4, 7, 10, 13},
                       {6, 8, 11, 15}};
    Test("Test3", (int *) matrix, 4, 4, 1, true);
}

//  1   2   8   9
//  2   4   9   12
//  4   7   10  13
//  6   8   11  15
// 要查找的数是数组中最大的数字
void Test4()
{
    int matrix[][4] = {{1, 2, 8,  9},
                       {2, 4, 9,  12},
                       {4, 7, 10, 13},
                       {6, 8, 11, 15}};
    Test("Test4", (int *) matrix, 4, 4, 15, true);
}

//  1   2   8   9
//  2   4   9   12
//  4   7   10  13
//  6   8   11  15
// 要查找的数比数组中最小的数字还小
void Test5()
{
    int matrix[][4] = {{1, 2, 8,  9},
                       {2, 4, 9,  12},
                       {4, 7, 10, 13},
                       {6, 8, 11, 15}};
    Test("Test5", (int *) matrix, 4, 4, 0, false);
}

//  1   2   8   9
//  2   4   9   12
//  4   7   10  13
//  6   8   11  15
// 要查找的数比数组中最大的数字还大
void Test6()
{
    int matrix[][4] = {{1, 2, 8,  9},
                       {2, 4, 9,  12},
                       {4, 7, 10, 13},
                       {6, 8, 11, 15}};
    Test("Test6", (int *) matrix, 4, 4, 16, false);
}

// 鲁棒性测试，输入空指针
void Test7()
{
    Test("Test7", nullptr, 0, 0, 16, false);
}

int main(int argc, char *argv[])
{
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
    Test6();
    Test7();

    return 0;
}
