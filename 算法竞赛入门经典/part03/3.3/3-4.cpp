#include "iostream"

const size_t StatSize = 10;

// num 在错误位置的数量
// = min((num 在答案中出现的次数 - num 在正确位置的次数), num 错误的次数)
bool new_round(const int *arr, int size)
{
    bool new_round = true;
    for (int i = 0; i < size; ++i)
    {
        if (*(arr + i) != 0)
        {
            new_round = false;
            break;
        }
    }
    return new_round;
}

int main(int argc, char **argv)
{
    std::istream &is = std::cin;
    int inputNum;
    int round = 1;
    for (is >> inputNum; inputNum != 0; is >> inputNum)
    {
        int numStat[StatSize];
        memset(numStat, 0, sizeof(numStat));

        int input[inputNum], answer[inputNum];
        for (int i = 0; i < inputNum; ++i)
        {
            is >> answer[i];
            numStat[answer[i]]++;
        }
        std::cout << "Game " << round++ << ":" << std::endl;
        while (true)
        {
            int errorPositionStat[StatSize], correctStat[StatSize];
            memset(errorPositionStat, 0, sizeof(errorPositionStat));
            memset(correctStat, 0, sizeof(correctStat));
            for (int i = 0; i < inputNum; ++i)
                is >> input[i];
            if (new_round(input, inputNum))
                break;
            for (int i = 0; i < inputNum; ++i)
            {
                if (input[i] == answer[i])
                {
                    correctStat[input[i]]++;
                }
                else
                {
                    for (int j = 0; j < inputNum; ++j)
                    {
                        if (answer[j] == input[i])
                        {
                            errorPositionStat[input[i]]++;
                            break;
                        }
                    }
                }
            }

            int a = 0, b = 0;
            for (int i = 0; i < StatSize; ++i)
            {
                a += correctStat[i];
                b += std::min(numStat[i] - correctStat[i], errorPositionStat[i]);
            }

            std::cout << "\t(" << a << ","
                      << b << ")" << std::endl;
        }
    }
}