#include "iostream"
#include "set"
#include "map"

static const int MAX_LEN = 10e6;

int           n;
int           a[MAX_LEN];
// 知识点
std::set<int> all;
// 记录知识点出现的次数
std::map<int, int> count;

void init()
{
	std::cin >> n;
	for (int i = 0; i < n; ++i)
	{
		std::cin >> a[i];
		all.insert(a[i]);
		std::cout << a[i] << " ";
	}
	std::cout << std::endl;
}

void solve()
{
	int ret = n;
	for (int start = 0, cur = 0; cur < n; ++cur)
	{
		if (count.count(a[cur]) == 0)
		{
			count.insert(std::make_pair(a[cur], 0));
		}
		++count.at(a[cur]);
		if (all.size() == count.size())
		{
			// [start, cur] 的区间内已经包含了所有的知识点，我们要开始缩小范围
			while (all.size() == count.size())
			{
				int &v = count.at(a[start]);
				if (--v == 0)
				{
					count.erase(a[start]);
				}
				++start;
			}
			// 这个时候的区间 [start - 1, end] 包含了所有的知识点，并且正好是最小范围
			ret = std::min(ret, cur - start + 2);
		}
	}

	std::cout << ret << std::endl;
}

int main(int argc, char **argv)
{
	init();
	solve();
	return 0;
}