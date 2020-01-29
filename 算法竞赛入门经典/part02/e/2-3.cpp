#include "iostream"

int main(int argc, char **argv)
{
    double sum = 0;
    for (int i = 0; ; ++i)
    {
        double term = 1.0 / (i * 2 + 1);
        if (i % 2 == 0)
        {
            sum += term;
        }
        else
        {
            sum -= term;
        }
        if (term < 1e-6)
            break;
    }

    std::cout << sum * 4 << std::endl;

    return 0;
}