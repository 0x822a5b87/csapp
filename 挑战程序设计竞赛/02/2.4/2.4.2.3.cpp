// POJ 3253
// 这个问题的解法作为计算霍夫曼编码而被熟知；
#include <vector>
#include "iostream"
#include "queue"

int arr[20010];
int num;

void init()
{
	std::cin >> num;
	for (int i = 0; i < num; ++i)
	{
		std::cin >> arr[i];
	}
}

int solve()
{
	int ret = 0, min, sec_min;
	std::priority_queue<int, std::vector<int>, std::greater<int> > q;
	for (int i = 0; i < num; ++i)
		q.push(arr[i]);
	while (true)
	{
		min = q.top();
		q.pop();
		sec_min = q.top();
		q.pop();
		ret += min + sec_min;
		if (q.empty())
		{
			break;
		}
		q.push(min + sec_min);
	}
	return ret;
}

int main(int argc, char **argv)
{
	init();
	std::cout << solve() << std::endl;
}

