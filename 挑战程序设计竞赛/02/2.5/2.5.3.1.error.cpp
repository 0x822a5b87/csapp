#include "iostream"
#include "queue"

const size_t MAX_V = 1024;

class edge
{
public:
	int from, to, cost;

	edge(int from, int to, int cost) : from(from), to(to), cost(cost)
	{}
};

struct EdgeCompare
{
	bool operator()(const edge &lhs, const edge &rhs)
	{
		return lhs.cost > rhs.cost;
	}
};

int V, E;

bool used[MAX_V];

std::priority_queue<edge, std::vector<edge>, EdgeCompare> q;

void init()
{
	std::cin >> V >> E;
	char from, to;
	int cost;
	for (int i = 0; i < E; ++i)
	{
		std::cin >> from >> to >> cost;
		int f = from - 'a';
		int t = to - 'a';
		q.push(edge(f, t, cost));
		q.push(edge(t, f, cost));
	}

	memset(used, 0, sizeof(used));
}

/*
 * 这是一个错误的解法，因为我没有每次去从已经构建的最小生成树子树的集 X 中去选取
 * 下一个元素。
 * 这可能导致部分节点没有被连通
 */
void prim()
{
	int mst = 0;
	while (!q.empty())
	{
		/*
		 * BUG：这里有个比较蛋疼的 BUG，最早我是使用的是 const edge &e0
		 * 一般而言，许多编译器的引用都是通过指针实现的，所以 g++ 这里实际上使用了一个指针
		 * 指向了 q.top() 的位置。
		 * 而一般优先队列都是基于二叉堆实现的，在我们 pop() 一个元素的时候，会把老的元素删除，
		 * 同时把新的元素放到堆的顶部，所以会出现一个情况， e0 实际上指向的是 pop() 执行之后
		 * 的堆顶元素。
		 *
		 * 所以我们观察到的是，第一个元素出现了一次，而最后一个元素出现了三次；
		 *
		 * 正常应该是：
		 *
		 * 0,2,1
		 * 2,0,1
		 * ...
		 * 4,1,10
		 * 1,4,10
		 *
		 * 实际看到的却是
		 * 0,2,1
		 * ...
		 * 4,1,10
		 * 1,4,10
		 * 1,4,10
		 *
		 * 而最后一次我们输出时的其实是未定义行为
		 */
		const edge e0 = q.top();
		q.pop();
		if (!used[e0.from] || !used[e0.to])
		{
			used[e0.from] = true;
			used[e0.to] = true;
			mst += e0.cost;

			std::cout << e0.from << " " << e0.to << " " << e0.cost << std::endl;
		}
	}
	std::cout << mst << std::endl;
}

int main(int argc, char **argv)
{
	init();
	prim();
}