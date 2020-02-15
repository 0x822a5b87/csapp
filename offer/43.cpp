// 把n个骰子扔在地上，所有骰子朝上一面的点数之和为s。输入n，打印出s的所有可能的值出现的概率。
#include "iostream"
#include "vector"

void Probability(int number)
{
    if (number <= 0)
        return;

    std::vector<int> prev, cur;
    prev.resize(7);
    for (int i = 1; i <= 6; ++i)
    {
        prev[i] = 1;
    }

    for (int round = 2; round <= number; ++round)
    {
        cur.resize(round * 6 + 1);
        for (int index = round; index <= 6 * round; ++index)
        {
            int sumOfIndex = 0;
            for (int add_cnt = 1; add_cnt <= 6; ++add_cnt)
            {
                int prev_index = index - add_cnt;
                if (prev_index < 1 || prev_index >= prev.size())
                {
                    continue;
                }
                sumOfIndex += prev[prev_index];
            }
            cur[index] = sumOfIndex;
        }

        std::swap(prev, cur);
    }

    for (int i = number; i <= 6 * number; ++i)
    {
        std::cout << prev[i] << " ";
    }
    std::cout << std::endl;
}

int main(int argc, char **argv)
{
    Probability(3);
}