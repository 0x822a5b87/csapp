//
// Created by 杜航宇 on 2019-10-02.
//
// 输入一个矩阵，按照从外向里以顺时针的顺序依次打印每一个数字

#include "iostream"

void PrintOuterRing(int **start, int initRow, int initCol, int width, int height)
{
    size_t currentRow = initRow, currentCol = initCol;

    for (size_t times = 0; times < width; ++times)
    {
        currentCol = initRow + times;
        std::cout << start[currentRow][currentCol] << " ";
    }

    for (size_t times = 1; times < height; ++times)
    {
        currentRow = initRow + times;
        std::cout << start[currentRow][currentCol] << " ";
    }

    for (size_t times = 1; times < width; ++times)
    {
        currentCol = currentCol - 1;
        std::cout << start[currentRow][currentCol] << " ";
    }

    for (size_t times = 1; times < height - 1; ++times)
    {
        currentRow = currentRow - 1;
        std::cout << start[currentRow][currentCol] << " ";
    }
}

void PrintMatrixClockWisely(int **numbers, int columns, int rows)
{
    int initRow = 0, initCol = 0, width = columns, height = rows;
    while (width > 0 && height > 0)
    {
        PrintOuterRing(numbers, initRow, initCol, width, height);
        ++initRow;
        ++initCol;
        width -= 2;
        height -= 2;
    }
}

// ==================== 测试代码 ====================
void Test(int columns, int rows)
{
    printf("Test Begin: %d columns, %d rows.\n", columns, rows);

    if (columns < 1 || rows < 1)
        return;

    int **numbers = new int *[rows];
    for (int i = 0; i < rows; ++i)
    {
        numbers[i] = new int[columns];
        for (int j = 0; j < columns; ++j)
        {
            numbers[i][j] = i * columns + j + 1;
        }
    }

    PrintMatrixClockWisely(numbers, columns, rows);
    printf("\n");

    for (int i = 0; i < rows; ++i)
        delete[] (int *) numbers[i];

    delete[] numbers;
}

int main(int argc, char *argv[])
{
    /*
    1
    */
    Test(1, 1);

    /*
    1    2
    3    4
    */
    Test(2, 2);

    /*
    1    2    3    4
    5    6    7    8
    9    10   11   12
    13   14   15   16
    */
    Test(4, 4);

    /*
    1    2    3    4    5
    6    7    8    9    10
    11   12   13   14   15
    16   17   18   19   20
    21   22   23   24   25
    */
    Test(5, 5);

    /*
    1
    2
    3
    4
    5
    */
    Test(1, 5);

    /*
    1    2
    3    4
    5    6
    7    8
    9    10
    */
    Test(2, 5);

    /*
    1    2    3
    4    5    6
    7    8    9
    10   11   12
    13   14   15
    */
    Test(3, 5);

    /*
    1    2    3    4
    5    6    7    8
    9    10   11   12
    13   14   15   16
    17   18   19   20
    */
    Test(4, 5);

    /*
    1    2    3    4    5
    */
    Test(5, 1);

    /*
    1    2    3    4    5
    6    7    8    9    10
    */
    Test(5, 2);

    /*
    1    2    3    4    5
    6    7    8    9    10
    11   12   13   14    15
    */
    Test(5, 3);

    /*
    1    2    3    4    5
    6    7    8    9    10
    11   12   13   14   15
    16   17   18   19   20
    */
    Test(5, 4);

    return 0;
}

