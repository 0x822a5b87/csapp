//
// Created by 杜航宇 on 2019-09-27.
//
// 调整数组顺序，使得奇数位于数组的前半部分，偶数位于数组的后半部分

#include "iostream"

using cond = bool(*)(const int &number);

void ReorderOddEven_2(int *data, size_t len, cond c);

bool IsEvent(const int &num)
{
    return num % 2 == 0;
}

void ReorderOddEven_1(int *data, size_t len)
{
    ReorderOddEven_2(data, len, IsEvent);
}


// 使用函数指针
void ReorderOddEven_2(int *data, size_t len, cond c)
{
    if (data == nullptr)
    {
        return;
    }
    for (int *start = data, *end = data + len - 1; start < end; ++start, --end)
    {
        while (start < end && c(*start))
        {
            ++start;
        }

        while (start < end && !c(*end))
        {
            --end;
        }

        if (start < end)
        {
            int tmp = *start;
            *start = *end;
            *end = tmp;
        }
    }
}

// ====================测试代码====================
void PrintArray(int numbers[], int length)
{
    if(length < 0)
        return;

    for(int i = 0; i < length; ++i)
        printf("%d\t", numbers[i]);

    printf("\n");
}

void Test(char* testName, int numbers[], int length)
{
    if(testName != nullptr)
        printf("%s begins:\n", testName);

    int* copy = new int[length];
    for(int i = 0; i < length; ++i)
    {
        copy[i] = numbers[i];
    }

    printf("Test for solution 1:\n");
    PrintArray(numbers, length);
    ReorderOddEven_1(numbers, length);
    PrintArray(numbers, length);

//    printf("Test for solution 2:\n");
//    PrintArray(copy, length);
//    ReorderOddEven_2(copy, length);
//    PrintArray(copy, length);

    delete[] copy;
}

void Test1()
{
    int numbers[] = {1, 2, 3, 4, 5, 6, 7};
    Test("Test1", numbers, sizeof(numbers)/sizeof(int));
}

void Test2()
{
    int numbers[] = {2, 4, 6, 1, 3, 5, 7};
    Test("Test2", numbers, sizeof(numbers)/sizeof(int));
}

void Test3()
{
    int numbers[] = {1, 3, 5, 7, 2, 4, 6};
    Test("Test3", numbers, sizeof(numbers)/sizeof(int));
}

void Test4()
{
    int numbers[] = {1};
    Test("Test4", numbers, sizeof(numbers)/sizeof(int));
}

void Test5()
{
    int numbers[] = {2};
    Test("Test5", numbers, sizeof(numbers)/sizeof(int));
}

void Test6()
{
    Test("Test6", nullptr, 0);
}

int main(int argc, char* argv[])
{
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
    Test6();

    return 0;
}

