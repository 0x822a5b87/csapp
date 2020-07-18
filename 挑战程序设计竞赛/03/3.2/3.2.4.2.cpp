#include <vector>
#include "iostream"

int n, W;
std::vector<int> w, v;

void init()
{
	int tmp;
	std::cin >> n;
	std::cout << n << std::endl;
	for (int i = 0; i < n; ++i)
	{
		std::cin >> tmp;
		w.push_back(tmp);
		std::cout << tmp << " ";
	}
	std::cout << std::endl;

	for (int i = 0; i < n; ++i)
	{
		std::cin >> tmp;
		v.push_back(tmp);
		std::cout << tmp << " ";
	}
	std::cout << std::endl;

	std::cin >> W;
	std::cout << W << std::endl;
}

/**
 * 枚举 lb 到 ub 区间所有可能的组合
 * @param ret 结果
 * @param lb  下界
 * @param ub  上界
 */
void do_enum(std::vector<std::pair<int, int>> &ret, size_t lb, size_t ub)
{
	for (size_t i = 0; i < (1u << (ub - lb)); ++i)
	{
		int w0 = 0, v0 = 0;
		size_t count = 0, e = i;
		while (e != 0)
		{
			if ((e & 1u) != 0)
			{
				w0 += w[lb + count];
				v0 += v[lb + count];
			}
			++count;
			e >>= 1u;
		}
		ret.emplace_back(std::make_pair(w0, v0));
	}
}

bool comp(const std::pair<int, int> l, const std::pair<int, int> r)
{
	return l.first < r.first;
}

std::vector<std::pair<int, int>> del_wrong(const std::vector<std::pair<int, int>> &pairs)
{
	std::vector<std::pair<int, int>> ret;
	size_t i = 0;
	// 注意，这里循环以直接到 pairs.size() - 1
	// 因为最后一个元素是全选，也就是说除非有重量为 0 的 item，否则它的重量一定是唯一的。
	for (; i < pairs.size() - 1; ++i)
	{
		int w0 = pairs[i].first, v0 = pairs[i].second;
		while (w0 == pairs[i + 1].first)
		{
			if (pairs[i + 1].second > v0)
			{
				v0 = pairs[i + 1].second;
			}
			i++;
		}
		ret.emplace_back(w0, v0);
	}

	ret.push_back(pairs[i]);
	return ret;
}

void solve()
{
	std::vector<std::pair<int, int>> left, right;
	do_enum(left, 0, n / 2);
	do_enum(right, n / 2, n);
	std::sort(right.begin(), right.end(), comp);
	std::vector<std::pair<int, int>> after_del = del_wrong(right);
	int max_weight = 0;
	std::for_each(std::begin(after_del), std::end(after_del), [](const std::pair<int, int> p){
		std::cout << p.first << " " << p.second << std::endl;
	});
	std::cout << std::endl;
	std::for_each(std::begin(left), std::end(left), [&](const std::pair<int, int> p){
		if (p.first > W)
		{
			return;
		}
		else if (p.first == W)
		{

			max_weight = std::max(p.second, max_weight);
		}
		else
		{
			const std::pair<int, int> &t = std::make_pair(W - p.first, 0xffff);
			const auto it = std::upper_bound(std::begin(after_del), std::end(after_del), t, comp) - 1;
			max_weight = std::max(max_weight, (*it).second + p.second);
		}
	});
	
	std::cout << max_weight << std::endl;
}

int main(int argc, char **argv)
{
	init();
	solve();
}