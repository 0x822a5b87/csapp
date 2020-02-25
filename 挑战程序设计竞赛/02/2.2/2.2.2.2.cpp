// 区间调度问题
// start 表示工作开始时间， stop 表示工作结束时间
// 要选择所做的工作保证 `参加工作的数量（不是持续时间）最多`

#include "vector"

int MaxWorkCnt(std::vector<int> start,
				std::vector<int> stop)
{
	size_t workCnt = 0;
	int stopTime = 0;
	for (size_t i = 0; i != start.size(); i++)
	{
		if (start[i] > stopTime)
		{
			stopTime = stop[i];
			workCnt++;
		}
	}
	return workCnt;
}

int main(int argc, char **argv)
{
	std::vector<int> start{1, 2, 4, 6, 8},
					 stop{3, 5, 7, 9, 10};

	assert(MaxWorkCnt(start, stop) == 3);
}
