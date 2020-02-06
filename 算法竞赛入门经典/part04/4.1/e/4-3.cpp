#include <cmath>
#include "iostream"

bool is_prime(int n)
{
    if (n <= 1)
        return false;

    int m = floor(sqrt(n) + 0.5);
    for (int i = 2; i <= m; ++i)
    {
        if (n % i == 0)
            return false;
    }

    return true;
}