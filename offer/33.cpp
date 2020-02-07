// 输入一个正整数数组，把数组里所有数字拼接起来排成一个数，打印能拼接出的所有数字中最小的一个。
// 例如输入数组{3,32,321}，则打印出这3个数字能排成的最小数字321323。

// 需要证明比较规则具有：自反性、对称性、传递性
// 1. 自反性
// AA == AA A == A
// 2. 对称性
// A < B <-> AB < BA
// 3. 传递性
// 试证明： A < B, B < C 则 A < C
// 假设 A 有 m 位，B 有 n 位， C 有 k 位，那么
// AB = A * 10n + B
// BA = B * 10m + A
// 且 AB < BA
// 经过变换得到
// A/(10m-1) < B/(10n-1)
// BC = B * 10k + C
// CB = C * 10n + B
// BC < CB
// B/(10n-1) < C/(10k-1)
// A/(10m-1) < C/(10k-1)
// A * 10k + C < C * 10m + A
// AC < CA
// 根据对称性得到 AC < CA

#include <sstream>
#include "iostream"
#include "vector"

std::string ToString(int number)
{
    std::ostringstream oss;
    oss << number;
    return oss.str();
}

std::string PrintMinNumber(std::vector<int> numbers)
{
    std::vector<std::string> v;
    v.reserve(numbers.size());
    for (const auto &num : numbers)
    {
        v.push_back(ToString(num));
    }
    std::sort(std::begin(v), std::end(v),
              [](const std::string &lhs, const std::string &rhs) -> bool
              {
                  std::string leftright = lhs + rhs;
                  std::string rightleft = rhs + lhs;
                  return leftright < rightleft;
              });

    std::string res;
    for (const auto &strNum : v)
    {
        res += strNum;
    }
    return res;
}

int main(int argc, char **argv)
{
    std::cout << PrintMinNumber({3334,3,3333332}) << std::endl;
    std::cout << PrintMinNumber({3,32,321}) << std::endl;
    // "333333323334"
    // "333333233334"
    // "333333233343"
}
