// 在字符串中找出第一个只出现一次的字符。如输入"abaccdeff"，则输出'b'。

/**
 * 1. 最早的程序存在一个 BUG，我使用了 set 保存 notRepeat 的元素，并在出现相同元素的时候把它从集合中删除；
 *    这会导致一个元素出现奇数次的时候被错误的保存在 notRepeat 中
 * 2. 最早我希望在 std::map 中同时保存字符出现的次数，以及字符第一次出现的索引。
 *    在结束计算之后，我们需要遍历 std::map 并找到字符第一次出现索引的最小位置。
 *    但是我没有注意到可以多次的遍历这个序列，因为这个字符串序列已经隐形的为我们保存字符第一次出现的索引
 */

#include <vector>
#include <map>
#include "iostream"

int FirstNotRepeatingChar(std::string str)
{
    std::map<char, int> countChar;
    for (const char     &ch : str)
    {
        const auto &search = countChar.find(ch);
        if (search == countChar.end())
        {
            countChar.insert({ch, 1});
        }
        else
        {
            search->second = search->second + 1;
        }
    }

    for (std::string::size_type sz = 0; sz < str.size(); ++sz)
    {
        const auto search = countChar.find(str[sz]);
        if (search->second == 1)
        {
            return sz;
        }
    }
    return -1;
}

int main(int argc, char **argv)
{
    std::string s("googgle");
    std::cout << FirstNotRepeatingChar(s) << std::endl;
}
