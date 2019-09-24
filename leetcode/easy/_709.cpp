//
// Created by 杜航宇 on 2019-09-24.
//

#include "iostream"
#include "algorithm"

class Solution {
public:
    std::string toLowerCase(const std::string &str) {
        const int diffInCase = 'A' - 'a';
        std::string ret;
        int i;
        for (i = 0; i != str.size(); i++)
        {
            int diff = str[i] - 'A';
            if (diff >= 0 && diff < 26)
            {
                ret += static_cast<char>(str[i] - diffInCase);
            }
            else
            {
                ret += str[i];
            }
        }
        return ret;
    }
};

int main()
{
    Solution solution;

    std::string s("Mymommaalwayssaid,\"Lifewaslikeaboxofchocolates.Youneverknowwhatyou'regonnaget.");
    std::cout << s << std::endl;

    const std::string &new_s = solution.toLowerCase(s);
    std::cout << s << std::endl;
    std::cout << new_s << std::endl;
}
