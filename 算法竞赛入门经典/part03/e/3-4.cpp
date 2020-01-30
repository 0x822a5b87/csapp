#include "iostream"

int main(int argc, char **argv)
{
    int sz;
    std::cin >> sz;
    int arr[sz][sz];


    int round = 1;
    for (int num = 1; num <= sz * sz; )
    {
        int minBoundary  = round - 1;
        int maxBoundary = sz - round;
        if (minBoundary == maxBoundary)
        {
            arr[minBoundary][maxBoundary] = num++;
        }
        // 在这里输出
        int x = minBoundary;
        int y = maxBoundary;
        for (; x < maxBoundary; ++x)
        {
            arr[x][y] = num++;
        }
        for (; y > minBoundary; --y)
        {
            arr[x][y] = num++;
        }
        for (; x > minBoundary; --x)
        {
            arr[x][y] = num++;
        }
        for (; y < maxBoundary; ++y)
        {
            arr[x][y] = num++;
        }

        ++round;
    }

    for (int x = 0; x < sz; ++x)
    {
        for (int y = 0; y < sz; ++y)
        {
            printf("%4d", arr[x][y]);
            printf(" ");
        }
        printf("\n");
    }
}