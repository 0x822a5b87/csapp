#include "iostream"

// 3-3 数数字
// UVa1225

int main(int argc, char **argv)
{
    size_t MaxValue = 100001;
    int stat[MaxValue];
    memset(stat, -1, sizeof(stat));

    int num;
    std::cin >> num;
    for (int i = 0; i < num; ++i)
    {
        int value;
        std::cin >> value;
        if (stat[value] < 0)
        {

        }
    }
}