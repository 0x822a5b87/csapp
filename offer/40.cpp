// 一个整型数组里除了两个数字之外，其他的数字都出现了两次。
// 请写程序找出这两个只出现一次的数字。要求时间复杂度是O（n），空间复杂度是O（1）。
#include "iostream"
#include "vector"

int lowestOneIndex(int num)
{

    int n = 0;
    while (num != 0)
    {
        if (num % 2 == 0)
        {
            ++n;
        }
        else
        {
            break;
        }
        num /= 2;
    }
    return n;
}

int bitOfIndex(int num, int index)
{
    num >>= index;
    return num % 2;
}

void FindNumsAppearOnce(std::vector<int> data, int *num1, int *num2)
{
    if (data.empty())
    {
        return;
    }

    int      xorRet = 0;
    for (int i : data)
    {
        xorRet ^= i;
    }

    int n = lowestOneIndex(xorRet);
    *num1 = 0;
    *num2 = 0;
    for (int i : data)
    {
        if (bitOfIndex(i, n) == 0)
        {
            *num1 = (*num1 ^ i);
        }
        else
        {
            *num2 = (*num2 ^ i);
        }
    }
}

int main(int argc, char **argv)
{
    std::vector<int> v{2, 4, 3, 6, 3, 2, 5, 5};
    std::cout << lowestOneIndex(0xf000) << std::endl;
    std::cout << bitOfIndex(0xf000, 12) << std::endl;
    int num1, num2;
    FindNumsAppearOnce(v, &num1, &num2);
    std::cout << num1 << " " << num2 << std::endl;
}
