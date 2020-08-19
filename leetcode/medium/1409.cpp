//
// Created by 0x822a5b87 on 2020/8/16.
//

#include "iostream"
#include "vector"
#include "map"

using namespace std;

class Solution
{
public:
	vector<int> processQueries(vector<int> &queries, int m)
	{
		map<int, int> v2i, i2v;
		for (int i = 0, v = 1; v <= m; ++i, ++v)
		{
			v2i[v] = i;
			i2v[i] = v;
		}

		vector<int> ans;
		for (const int q : queries)
		{
			int &index = v2i[q];
			ans.push_back(index);

			int tmp = i2v[index];
			i2v[index] = i2v[0];
			i2v[0] = tmp;

			v2i[q] = 0;
			v2i[0] = index;
		}
		return ans;
	}
};