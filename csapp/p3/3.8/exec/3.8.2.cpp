//
// Created by 杜航宇 on 2019-08-08.
//

#include "iostream"

int main()
{
    int arr[3][3] = {{1, 2, 3},
                     {4, 5, 6},
                     {7, 8, 9}};

    for (const auto &row : arr)
    {
        for (const auto &col : row)
        {
            std::cout << &col << "= " << col << std::endl;
        }
    }
}
