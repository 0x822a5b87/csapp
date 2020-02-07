// 输入一个整数n，求从1到n这n个整数的十进制表示中1出现的次数。
// 例如输入12，从1到12这些整数中包含1 的数字有1，10，11和12，1一共出现了5次
#include <vector>
#include "iostream"

int NumberOf1(int num)
{
    int count = 0;
    while (num > 0)
    {
        if (num % 10 == 1)
        {
            ++count;
        }
        num = num / 10;
    }
    return count;
}

// 假设一个数字是 [An, An-1, An-2, ..., Am, .., A3, A2, A1]
// 那么，出现在 Am == 1 的所有数字数量为
// if (Am > 1)
//      return (An * pow(10, (n - m - 1)) + .. + Am+1) * pow(10, m-1)
//      return ([An, An-1, ..., An-m+1] + 1) * pow(10, m - 1)
// else if (Am == 1)
//      return  ([An, An-1, ..., An-m+1]) * pow(10, m - 1)
//              + [An, An-1, ..., An-m+1] * ([Am-1, ..., A2, A1] + 1)
// else
//      return 0

int NumberOf1Between1AndN_Solution(int n)
{
    int placeTotal = 0;
    for (int place = 1; n >= place; place *= 10)
    {
        int left     = n / (place * 10);
        int right    = n % place;
        int placeNum = (n / place) % 10;
        if (placeNum > 1)
        {
            placeTotal += (left + 1) * place;
        }
        else if (placeNum == 1)
        {
            placeTotal += (left * place) + right + 1;
        }
        else
        {
            placeTotal += left * place;
        }
    }

    return placeTotal;
}

int main(int argc, char **argv)
{
    for (int i = 123456789; i < 123456789; ++i)
    {
        int total = 0;
        for (int j = 1; j <= i; ++j)
        {
            total += NumberOf1(j);
        }
        int solution = NumberOf1Between1AndN_Solution(i);
        if (total != solution)
        {
            std::cout << i << " " << total << " " << solution << std::endl;
        }
    }
}
