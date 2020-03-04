#include "iostream"
#include "queue"

int n, l, p;
int a[1000], b[10000];

void init()
{
	std::cin >> n >> l >> p;
	for (size_t i = 0; i < n; ++i)
	{
		std::cin >> a[i] >> b[i];
	}

	std::cout << "n = " << n << std::endl;
	std::cout << "l = " << l << std::endl;
	std::cout << "p = " << p << std::endl;
}

/*
 * BUG1：题目理解错误， a[i] 不是距离 a[i-1] 的距离，而是距离起点的距离
 */
int solve()
{
	std::priority_queue<int> q;

	// pos 当前位置
	// cnt 加油次数
	// dis 距离下一个加油站的距离
	int pos = p, cnt = 0, dis = 0;
	// 注意，这里是一个非常经典的优化。我们将终点看做一个加油站，这使得我们可以不用去处理边界条件
	// 这种优化叫做哨兵
	a[n] = l;
	/*
	 * 经过每一个加油站，我们都把加油站放到优先队列中。
	 * 当油不够的时候，我们可以从已经经过的加油站中找出加油最多的那个加油站
	 */
	for (int i = 0; i < n; ++i)
	{
		while (a[i] > pos && !q.empty())
		{
			cnt++;
			pos += q.top();
			q.pop();
		}
		if (a[i] > pos)
		{
			return -1;
		}

		// 经过了一个加油站
		q.push(b[i]);
	}

	return cnt;
}

int main(int argc, char **argv)
{
	init();
	std::cout << solve() << std::endl;
}