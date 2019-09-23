//
// Created by 杜航宇 on 2019-09-23.
//

#include <vector>
#include <deque>
#include "iostream"

void insert(std::deque<int> &q, int num)
{
    q.push_back(num);
}

int main()
{
    std::deque<int> q;

    for (int i = 0; i != 10; ++i)
    {
        insert(q, i);
    }

    std::cout << q.size() << std::endl;
}
