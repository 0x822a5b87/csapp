// 3.4.4
// 习题 3-1 得分
#include "iostream"

constexpr size_t MaxLen = 80 + 10;

int main(int argc, char **argv)
{
    size_t cnt;
    std::cin >> cnt;
    for (size_t i = 0; i < cnt; ++i)
    {
        std::string word;
        std::cin >> word;
        size_t score = 0, total = 0;
        for (const auto &ch : word)
        {
            if (ch == 'O')
            {
                ++score;
            }
            else
            {
                score = 0;
            }
            total += score;
        }

        std::cout << total << std::endl;
    }
}
