//
// Created by 0x822a5b87 on 2020/8/16.
//

#include "iostream"
#include "vector"

using namespace std;

class Solution
{
public:
	vector<vector<int>> floodFill(vector<vector<int>> &image, int sr, int sc, int newColor)
	{
		if (image.empty())
		{
			return vector<vector<int>>();
		}

		int h        = image.size(), w = image[0].size();
		int curColor = image[sr][sc];

		std::vector<vector<int>> v;
		v.emplace_back(vector<int>{sr, sc});
		while (!v.empty())
		{
			vector<int> &point = v.back();
			v.pop_back();

			std::cout << image[point[0]][point[1]] << std::endl;
			if (legalPoint(point[1], point[0], w, h)
				&& image[point[0]][point[1]] == curColor)
			{
				v.push_back({point[0], point[1]});
			}
			image[point[0]][point[1]] = newColor;
		}

		return image;
	}

private:
	bool legalPoint(int cw, int ch, int w, int h)
	{
		return cw >= 0 && cw < w && ch >= 0 && ch < h;
	}
};

int main(int argc, char **argv)
{
	vector<std::vector<int>> v{
			{1, 1, 1},
			{1, 1, 0},
			{1, 0, 1}
	};

	Solution solution;
	solution.floodFill(v, 1, 1, 2);

	for (int i = 0; i < v.size(); ++i)
	{
		for (int j = 0; j < v[i].size(); ++j)
		{
			std::cout << v[i][j] << " ";
		}
		std::cout << std::endl;
	}
}