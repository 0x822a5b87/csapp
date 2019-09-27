//
// Created by 杜航宇 on 2019-09-26.
//
// 实现 '.' 和 '*' 的正则匹配功能
//

#include "iostream"

bool matchCore(const char *str, const char *pattern)
{
    if (*pattern == '\0' && *str == '\0')
    {
        return true;
    }

    if (*pattern == '\0' && *str != '\0')
    {
        return false;
    }

    // 到这里还可能出现的情况是
    // 1. *pattern != '\0' && *str != '\0'
    // 2. *pattern != '\0' && *str == '\0'

    // 对于两种情况，我们都可以分为以下三种情况
    // 1. *pattern != '.'
    // 2. *pattern == '.' && *++pattern != '*'
    // 3. *pattern == '.' && *++pattern == '*'

    // 普通字符
    if (*pattern != '.')
    {
        char nextPattern = *(pattern + 1);
        if (nextPattern == '*')
        {
            while (*str != '\0'
                   && *str == *pattern)
            {
                // 可以匹配0个或者配n个
                if (matchCore(str, pattern + 2))
                {
                    return true;
                }
                ++str;
            }
            return matchCore(str, pattern + 2);
        }
        else
        {
            return *pattern == *str && matchCore(++str, ++pattern);
        }
    }

    // 后面没有跟着 * 的 . 字符
    if (*++pattern != '*')
    {
        return matchCore(++str, pattern);
    }

    // .*
    char currentPatternCh = *++pattern;
    while (*str != '\0'
           && *str != currentPatternCh)
    {
        if (matchCore(str, pattern))
        {
            return true;
        }
        // 可以匹配0个或者配n个
        ++str;
    }
    return matchCore(str, pattern);
}


bool match(const char *str, const char *pattern)
{
    if (str == nullptr || pattern == nullptr)
    {
        return false;
    }

    return matchCore(str, pattern);
}

//bool match(const char *str, const char *pattern)
//{
//    if (str == nullptr || pattern == nullptr)
//    {
//        return false;
//    }
//
//    matchCore(str, pattern);
//
//    size_t strIndex = 0, regexIndex = 0;
//    char   currentStr, currentRegex;
//
//    do
//    {
//        currentStr = str[strIndex], currentRegex = pattern[regexIndex];
//        if (currentRegex == '\0')
//        {
//            return false;
//        }
//
//        if (currentRegex == '.')
//        {
//            // 如果在 . 之后跟着 *， 那么它它可以匹配 0-n 个字符
//            // 直到在 str 中匹配到第一个紧跟着 '*' 字符相同的字符
//            currentRegex = pattern[++regexIndex];
//            if (currentRegex != '*')
//            {
//                continue;
//            }
//            currentStr = str[++strIndex];
//            currentRegex = pattern[++regexIndex];
//
//            while ((currentStr = str[++strIndex]) != '\0'
//                   && currentStr != currentRegex)
//            {
//
//            }
//
//            continue;
//        }
//
//        if (currentStr == currentRegex)
//        {
//            ++strIndex;
//            ++regexIndex;
//            continue;
//        }
//
//        return false;
//    } while (str[strIndex] != '\0' && pattern[regexIndex] != '\0');
//
//    return currentStr == '\0' && currentRegex == '\0';
//}

// ====================测试代码====================
//void Test(const char *testName, const char *string, const char *pattern, bool expected)
//{
//    if (testName != nullptr)
//        printf("%s begins: ", testName);
//
//    if (match(string, pattern) == expected)
//        printf("Passed.\n");
//    else
//        printf("FAILED.\n");
//}

void Test(const char *testName, const char *string, const char *pattern, bool expected)
{
    if (match(string, pattern) != expected)
    {
        printf("%s begins: ", testName);
        printf("FAILED.\n");
    }
}

int main(int argc, char *argv[])
{
    Test("Test01", "", "", true);
    Test("Test02", "", ".*", true);
    Test("Test03", "", ".", false);
    Test("Test04", "", "c*", true);
    Test("Test05", "a", ".*", true);
    Test("Test06", "a", "a.", false);
    Test("Test07", "a", "", false);
    Test("Test08", "a", ".", true);
    Test("Test09", "a", "ab*", true);
    Test("Test10", "a", "ab*a", false);
    Test("Test11", "aa", "aa", true);
    Test("Test12", "aa", "a*", true);
    Test("Test13", "aa", ".*", true);
    Test("Test14", "aa", ".", false);
    Test("Test15", "ab", ".*", true);
    Test("Test16", "ab", ".*", true);
    Test("Test17", "aaa", "aa*", true);
    Test("Test18", "aaa", "aa.a", false);
    Test("Test19", "aaa", "a.a", true);
    Test("Test20", "aaa", ".a", false);
    Test("Test21", "aaa", "a*a", true);
    Test("Test22", "aaa", "ab*a", false);
    Test("Test23", "aaa", "ab*ac*a", true);
    Test("Test24", "aaa", "ab*a*c*a", true);
    Test("Test25", "aaa", ".*", true);
    Test("Test26", "aab", "c*a*b", true);
    Test("Test27", "aaca", "ab*a*c*a", true);
    Test("Test28", "aaba", "ab*a*c*a", false);
    Test("Test29", "bbbba", ".*a*a", true);
    Test("Test30", "bcbbabab", ".*a*a", false);
    Test("Test31", "a", "a*a", true);

    return 0;
}
