// 输入 n 个整数，找出其中最小的 K 个数。
// 例如输入 4,5,1,6,2,7,3,8 这 8 个数字， 则最小的 4 个数字是 1,2,3,4。
#include <iostream>
#include <vector>
#include <queue>

std::vector<int> GetLeastNumbers_Solution(std::vector<int> input, int k)
{
    std::priority_queue<int, std::vector<int>> pq;
    for (const auto &num : input)
    {
        if (pq.size() < k)
        {
            pq.push(num);
        }
        else
        {
            try
            {
                if (num < pq.top())
                {
                    pq.pop();
                    pq.push(num);
                }
            }
            catch (std::exception &e)
            {}
        }
    }
    std::vector<int> ret;
    while(!pq.empty())
    {
        ret.push_back(pq.top());
        pq.pop();
    }
    return ret;
}

int main(int argc, char **argv)
{
    std::vector<int> input{4, 5, 1, 6, 2, 7, 3, 8};

    const std::vector<int> &v = GetLeastNumbers_Solution(input, 4);
    for (const auto &num : v)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}
