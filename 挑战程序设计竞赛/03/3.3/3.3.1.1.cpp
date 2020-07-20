#include <vector>
#include "iostream"

const int MAX_N = 1 << 17;

std::vector<int> data;
int              n;

void init(int num)
{
	n = 1;
	while (n < num)
	{
		n *= 2;
	}

	data.resize(2 * n - 1);
	std::fill(std::begin(data), std::end(data), INT_MAX);
}

/**
 * 将第 k 个值 (0 - indexed) 更新为 a
 * @param k 要更新的值的索引
 * @param a 更新后的数值
 */
void update(int k, int a)
{
	k += n - 1;
	data[k] = a;
	while (k > 0)
	{
		k = (k - 1) / 2;
		data[k] = std::min(data[k * 2 + 1], data[k * 2 + 2]);
	}
}

/**
 * 求 [a, b) 的最小值
 * @param k 节点编号
 * @param l r 表示此节点的区间是 [l, r)
 * @return
 */
int query(int a, int b, int k, int l, int r)
{
	// 一定要注意，这里必须有 =，因为 [a, b) 和 [l, r) 都是左开右闭的区间
	// (l, (l + r) / 2) 和 ((l + r) / 2, r) 这两个区间可能会死循环
	// 例如，对于 l == 5, r == 6 可能一直死循环
	if (r <= a || b <= l)
	{
		return INT_MAX;
	}
	if (a <= l && r <= b)
	{
		return data[k];
	}
	return std::min(query(a, b, k * 2 + 1, l, (l + r) / 2),
					query(a, b, k * 2 + 2, (l + r) / 2, r));
}

//int main(int argc, char **argv)
//{
//	init(8);
//
//	update(0, 5);
//	update(1, 3);
//	update(2, 7);
//	update(3, 9);
//	update(4, 6);
//	update(5, 4);
//	update(6, 1);
//	update(7, 2);
//
//	assert(query(0, 8, 0, 0, 8) == 1);
//	assert(query(1, 3, 0, 0, 8) == 3);
//	assert(query(2, 6, 0, 0, 8) == 4);
//	assert(query(0, 0, 0, 0, 8) == INT_MAX);
//	assert(query(7, 7, 0, 0, 8) == INT_MAX);
//	assert(query(5, 7, 0, 0, 8) == 1);
//}