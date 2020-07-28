#include <vector>
#include "iostream"

const int BUCKET_SIZE = 4;

int                            n, m;
std::vector<int>               a;
std::vector<std::vector<int> > q;

void init()
{
	std::cin >> n >> m;

	int      tmp;
	for (int i = 0; i < n; ++i)
	{
		std::cin >> tmp;
		a.push_back(tmp);
		std::cout << tmp << " ";
	}

	std::cout << std::endl;

	for (int i = 0; i < m; ++i)
	{
		std::vector<int> v;
		std::cin >> tmp;
		v.push_back(tmp);

		std::cin >> tmp;
		v.push_back(tmp);

		std::cin >> tmp;
		v.push_back(tmp);

		q.push_back(v);

		std::cout << v[0] << " " << v[1] << " " << v[2] << std::endl;
	}
}

/**
 * 基于分桶法实现
 */
void solve1()
{
	// 我们使用 numbs 来实现对 k-th number 的二分查找
	std::vector<int> nums(a);
	std::sort(std::begin(nums), std::end(nums));

	// 分桶并对每个桶里的数据进行排序
	std::vector<std::vector<int> > buckets;
	buckets.resize(n / BUCKET_SIZE + 1);
	for (int i = 0; i < n; ++i)
	{
		int bucket_index = i / BUCKET_SIZE;
		buckets[bucket_index].push_back(a[i]);
	}

	for (int i = 0; i < (n + 1) / BUCKET_SIZE; ++i)
	{
		std::sort(buckets[i].begin(), buckets[i].end());
	}

	for (auto & bucket : buckets)
	{
		std::cout << "[";
		for (int j : bucket)
		{
			std::cout << j << ",";
		}
		std::cout << "],";
	}
	std::cout << std::endl;

	// 对输入数组 m 里的每个三元数组求解
	for (int i = 0; i < m; ++i)
	{
		const int l  = q[i][0], r = q[i][1], k = q[i][2];
		// 开始对数组进行二分查找
		int       lb = 0, ub = n - 1, mid = 0;
		// 二分查找都必须使用 lb <= ub 这个条件，并且变化 mid 的时候必须根据
		// 上界或者下界来分别 +1 和 -1
		while (lb <= ub)
		{

			mid = (lb + ub) / 2;
			std::cout << lb << " " << mid << " " << ub << std::endl;
			int x   = nums[mid];

			int tl = l, tr = r, c = 0;
			// 搜索左边不包含在桶内的所有区间
			while (tl <= tr && tl % BUCKET_SIZE != 0)
			{
				if (a[tl++] <= x)
				{
					++c;
				}
			}
			// 搜索右边不包含在桶内的所有区间
			while (tl <= tr && tr % BUCKET_SIZE != (BUCKET_SIZE - 1))
			{
				if (a[tr--] <= x)
				{
					++c;
				}
			}
			// 搜索每一个完全包含在桶内的自区间
			while (tl < tr)
			{
				int bucket_index = tl / BUCKET_SIZE;
				c += std::upper_bound(buckets[bucket_index].begin(), buckets[bucket_index].end(), x)
					 - buckets[bucket_index].begin();

				tl += BUCKET_SIZE;
			}

			if (c >= k)
			{
				ub = mid - 1;
			}
			else
			{
				lb = mid + 1;
			}
		}
		std::cout << nums[lb] << std::endl;
	}
}

int main(int argc, char **argv)
{
	init();
	solve1();
}