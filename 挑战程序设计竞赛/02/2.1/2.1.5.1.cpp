#include <vector>
#include <sstream>
#include <deque>
#include <utility>
#include "iostream"

class MazeStat
{
public:
	int    prev_i;
	int    prev_j;
	int    cur_i;
	int    cur_j;
	size_t steps;

	MazeStat()
			: prev_i(0), prev_j(0), steps(10000), cur_i(0), cur_j(0)
	{

	}

	MazeStat(int prevI, int prevJ, int curI, int curJ, size_t steps)
			: prev_i(prevI), prev_j(prevJ), cur_i(curI),
			  cur_j(curJ), steps(steps)
	{}
};

void step_into
		(const std::vector<std::vector<int> > &input,
		 std::vector<std::vector<MazeStat> > &s,
		 std::deque<MazeStat> &q,
		 const std::pair<int, int> &p,
		 MazeStat current, size_t height, size_t width)
{
	size_t i = current.cur_i + p.first;
	size_t j = current.cur_j + p.second;
	if (i < 0 || i >= height || j < 0 || j >= width || input[i][j] == 1)
	{
		return;
	}
	size_t step = current.steps + 1;
	if (s[i][j].steps > step)
	{
		s[i][j].steps  = step;
		s[i][j].prev_i = current.cur_i;
		s[i][j].prev_j = current.cur_j;
		MazeStat new_s(current.cur_i, current.cur_j, i, j, step);
		q.push_back(new_s);
	}
}

int main(int argc, char **argv)
{
	size_t                         height = 0, width = 0;
	std::vector<std::vector<int> > input;
	std::string                    line;
	while (std::getline(std::cin, line))
	{
		height++;
		std::istringstream is(line);
		// 解释一下这里的代码，vector 可以接受两个迭代器 begin 和 end 来初始化
		// 而 is 的迭代器当迭代结束的时候等于空迭代器
		input.push_back(std::vector<int>(std::istream_iterator<int>(is),
										 std::istream_iterator<int>()));
	}

	if (input.empty())
	{
		return 0;
	}
	else if (input.size() == 1)
	{
		return input[0].size();
	}

	std::vector<std::vector<MazeStat> > stats;

	for (size_t i = 0; i < input.size(); ++i)
	{
		std::vector<MazeStat> v;
		for (size_t           j = 0; j < input[i].size(); ++j)
		{
			width = input[i].size();
			v.push_back(MazeStat(0, 0, i, j, 1000));
		}
		stats.push_back(v);
	}

	std::pair<int, int>  up    = std::make_pair(-1, 0);
	std::pair<int, int>  down  = std::make_pair(1, 0);
	std::pair<int, int>  left  = std::make_pair(0, -1);
	std::pair<int, int>  right = std::make_pair(0, 1);
	std::deque<MazeStat> q;
	q.push_back(MazeStat(-1, -1, 0, 0, 0));
	stats[0][0].steps = 0;

	while (!q.empty())
	{
		MazeStat s = q.front();
		q.pop_front();
		step_into(input, stats, q, up, s, height, width);
		step_into(input, stats, q, down, s, height, width);
		step_into(input, stats, q, left, s, height, width);
		step_into(input, stats, q, right, s, height, width);
	}

	for (size_t i = height - 1, j = width - 1; i != 0 || j != 0;)
	{
		/* 之前这里有个很严重的 BUG，我在修改 j 之前修改了 i 的值 */
		q.push_back(stats[i][j]);
		int tmp_i = stats[i][j].prev_i;
		int tmp_j = stats[i][j].prev_j;
		i = tmp_i;
		j = tmp_j;
	}

	std::cout << "(0, 0)" << std::endl;
	while (!q.empty())
	{
		MazeStat &b = q.back();
		q.pop_back();
		std::cout << "(" << b.cur_i << ", " << b.cur_j << ")" << std::endl;
	}
}

// POJ-3984
// 定义一个二维数组：
//
//int maze[5][5] = {
//
//	0, 1, 0, 0, 0,
//
//	0, 1, 0, 1, 0,
//
//	0, 0, 0, 0, 0,
//
//	0, 1, 1, 1, 0,
//
//	0, 0, 0, 1, 0,
//
//};
//
//它表示一个迷宫，其中的1表示墙壁，0表示可以走的路，只能横着走或竖着走，不能斜着走，要求编程序找出从左上角到右下角的最短路线。
//Input
//
//一个5 × 5的二维数组，表示一个迷宫。数据保证有唯一解。
//Output
//
//左上角到右下角的最短路径，格式如样例所示。
//Sample Input
//
//0 1 0 0 0
//0 1 0 1 0
//0 0 0 0 0
//0 1 1 1 0
//0 0 0 1 0
//Sample Output
//
//(0, 0)
//(1, 0)
//(2, 0)
//(2, 1)
//(2, 2)
//(2, 3)
//(2, 4)
//(3, 4)
//(4, 4)

