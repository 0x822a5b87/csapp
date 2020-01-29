#include "iostream"

int main(int argc, char **argv)
{
    int numOfInput;

    do
    {
        std::cin >> numOfInput;
        int num;
        int max = 0, min = 0, sum = 0, count = 0;
        bool init = false;
        while (true)
        {
            if (count == numOfInput)
                break;
            std::cin >> num;
            if (!init)
            {
                max = num;
                min = num;
                init = true;
            }
            if (num > max)
                max = num;
            if (num < min)
                min = num;
            sum += num;
            ++count;
        }
        if (init)
        {
            printf("%d %d %.3f\n", min, max, (double) sum / count);
        }
    } while (numOfInput != 0);

    return 0;
}