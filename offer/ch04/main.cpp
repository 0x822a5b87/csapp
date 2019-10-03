//
// Created by 杜航宇 on 2019-09-25.
//

#include <vector>
#include "iostream"
#include "../Utilities/BinaryTree.hpp"

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

int main()
{
    int rows = 4, columns = 4;
    int **numbers = new int *[rows];
//    for (int i = 0; i < rows; ++i)
//    {
//        numbers[i] = new int[columns];
//        for (int j = 0; j < columns; ++j)
//        {
//            numbers[i][j] = i * columns + j + 1;
//        }
//    }
//
//    for (int i = 0; i < rows; ++i)
//    {
//        for (int j = 0; j < columns; ++j)
//        {
//            std::cout << numbers[i][j] << " ";
//        }
//        std::cout << std::endl;
//    }
//
//    std::cout << std::endl;
//
//    PrintOuterRing(numbers, 0, 0, 4, 4);
//    std::cout << std::endl << "1 2 3 4 8 12 16 15 14 13 9 5" << std::endl;
//
//    PrintOuterRing(numbers, 1, 1, 2, 2);
//    std::cout << std::endl << "6 7 11 10" << std::endl;


    rows = 2, columns = 4;
    numbers = new int *[rows];
    for (int i = 0; i < rows; ++i)
    {
        numbers[i] = new int[columns];
        for (int j = 0; j < columns; ++j)
        {
            numbers[i][j] = i * columns + j + 1;
        }
    }

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < columns; ++j)
        {
            std::cout << numbers[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
    PrintOuterRing(numbers, 0, 0, 4, 2);
}
