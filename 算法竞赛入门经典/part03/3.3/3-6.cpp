#include "iostream"

constexpr size_t MaxLen = 1024;

// 在环装字符串 s 中，以p开头的表示法和以q开头的表示法哪个更大
bool less(const char *s, int p, int q)
{
    int n = strlen(s);
    for (int i = 0; i < n; ++i)
    {
        char pc = s[(p + i) % n];
        char qc = s[(q + i) % n];
        if (pc != qc)
        {
            return qc > pc;
        }
    }
    return false;
}

int main(int argc, char **argv)
{
    char word[MaxLen];
    std::cin >> word;

    size_t len = strlen(word);

    // less 可以比较两个不同的表示法的字符序
    // 我们把最小的那个表示法的开头索引用 ans 表示，每次循环更新 ans 即可
    int ans = 0;
    for (size_t i = 1; i < len; ++i)
    {
        if (less(word, i, ans))
        {
            ans = i;
        }
    }

    for (size_t i = 0; i < len; ++i)
    {
        std::cout << word[(ans + i) % len];
    }
    std::cout << std::endl;
}