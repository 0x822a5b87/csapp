//
// Created by 0x822a5b87 on 2020/9/7.
//

#include <queue>
#include "iostream"
#include "vector"
#include "map"

using namespace std;

class Solution
{
public:
	vector<int> topKFrequent(vector<int> &nums, int k)
	{
		map<int, int>  m;
		for (const int &num : nums)
		{
			const map<int, int>::iterator &it = m.find(num);
			if (it == m.end())
			{
				m.emplace(num, 1);
			}
			else
			{
				++it->second;
			}
		}

		auto compare = [](std::pair<int, int> lhs, std::pair<int, int> rhs)
		{
			return lhs.second > rhs.second;
		};

		std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, decltype(compare)> q(compare);

		for (const auto &entry : m)
		{
			if (q.size() < k)
			{
				q.push(std::make_pair(entry.first, entry.second));
			}
			else
			{
				const std::pair<int, int> &num = q.top();
				if (num.second < entry.second)
				{
					q.pop();
					q.push(std::make_pair(entry.first, entry.second));
				}
			}
		}

		vector<int> v;

		while (!q.empty())
		{
			const auto &p = q.top();
			v.push_back(p.first);
			q.pop();
		}

		return v;
	}
};

int main(int argc, char **argv)
{
	Solution          solution;
	vector<int>       nums = {5, 2, 5, 3, 5, 3, 1, 1, 3};
	const vector<int> &v   = solution.topKFrequent(nums, 2);
	for (int          i : v)
	{
		std::cout << i << " ";
	}
	std::cout << std::endl;
}