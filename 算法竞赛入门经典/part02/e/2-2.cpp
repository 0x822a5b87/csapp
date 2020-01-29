#include "iostream"

int main(int argc, char **argv)
{
    long num, cnt = 0;
    std::cin >> num;
    while (num > 1)
    {
        if (num % 2 == 0)
        {
            num /= 2;
        }
        else
        {
            num = 3 * num + 1;
        }
        ++cnt;
    }

    std::cout << cnt << std::endl;
}