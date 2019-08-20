//
// Created by 杜航宇 on 2019-08-18.
//

#include "iostream"

void func(int *pt)
{
    *(pt + 1) = 3;
}

int main()
{
    int arr[2] = {1, 2};
    func(arr);
    std::cout << arr[0] << std::endl;
    std::cout << arr[1] << std::endl;
}
