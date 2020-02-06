#include <vector>
#include "iostream"

using StrSize = std::string::size_type;

constexpr std::vector<unsigned int>::size_type LetterNum = 26;


StrSize countIndex(char ch)
{
    int upperChar = std::toupper(ch);
    return upperChar - 'A';
}

bool canChange(const std::string &word0,
               const std::string &word1)
{
    StrSize l0 = word0.size();
    StrSize l1 = word1.size();
    if (l0 != l1)
        return false;

    std::vector<unsigned int> word0Cnt(LetterNum), word1Cnt(LetterNum);
    for (StrSize i = 0; i < l0; ++i)
    {
        word0Cnt[countIndex(word0[i])]++;
        word1Cnt[countIndex(word1[i])]++;
    }

    std::sort(word0Cnt.begin(), word0Cnt.end());
    std::sort(word1Cnt.begin(), word1Cnt.end());

    for (size_t letterIndex = 0; letterIndex < LetterNum; ++letterIndex)
    {
        if (word0Cnt[letterIndex] != word1Cnt[letterIndex])
            return false;
    }

    return true;
}

int main(int argc, char **argv)
{
    std::string word0, word1;
    std::cin >> word0;
    std::cin >> word1;

    if (canChange(word1, word1))
        std::cout << "YES" << std::endl;
    else
        std::cout << "NO" << std::endl;
}