// 线段树
// 单点修改，区域查询
#include "iostream"

struct tree
{
	int l, r, sum;
};

const int MAX_LEN = 100;

int  n;
int  input[MAX_LEN];
tree data[MAX_LEN];

void init()
{
	std::cin >> n;
	for (int i = 0; i < n; ++i)
	{
		data[i] = tree();
		std::cin >> input[i];
	}
}

int search(int i, int l, int r)
{
	// 如果不在区间内那么直接返回0
	if (r < data[i].l || data[i].r < l)
	{
		return 0;
	}
	// 如果区间完全包含了线段树的某一段，那么直接返回结果而不用查询详细值
	if (l <= data[i].l && data[i].r <= r)
	{
		return data[i].sum;
	}

	return search(i * 2 + 1, l, r) + search(i * 2 + 2, l, r);
}

int add(int &o, int &v)
{
	int diff = v - o;
	o = v;
	return diff;
}

int update(int i, int dis, int v)
{
	if (data[i].l == data[i].r)
	{
		return add(data[i].sum, v);
	}

	tree chl = data[i * 2 + 1], chr = data[i * 2 + 2];
	if (chl.l <= dis && dis <= chl.r)
	{
		int diff = update(i * 2 + 1, dis, v);
		data[i].sum += diff;
		return diff;
	}
	else if (chr.l <= dis && dis <= chr.r)
	{
		int diff = update(i * 2 + 2, dis, v);
		data[i].sum += diff;
		return diff;
	}
	else
	{
		std::cout << "error" << std::endl;
		return 0;
	}
}

/**
 * 递归构建线段树
 * @param i 线段树的节点 i
 * @param l 这个点代表的线段的左下标
 * @param r 这个点代表的线段的右下标
 */
void build(int i, int l, int r)
{
	data[i].l = l;
	data[i].r = r;
	// 如果是叶子节点
	if (l == r)
	{
		data[i].sum = input[l];
		return;
	}
	int mid   = (l + r) >> 1;
	// 分别构造左子树和右子树
	build(i * 2 + 1, l, mid);
	build(i * 2 + 2, mid + 1, r);
	// 刚才我们发现的性质return ;
	data[i].sum = data[i * 2 + 1].sum + data[i * 2 + 2].sum;
}

void print_data()
{
	std::cout << "========================" << std::endl;
	for (int i = 0; i < 2 * n - 1; ++i)
	{
		std::cout << data[i].l << " " << data[i].r << " " << data[i].sum << std::endl;
	}
	std::cout << "========================" << std::endl;
}

int main(int argc, char **argv)
{
	init();
	build(0, 0, 4);
	assert(search(0, 0, 3) == 10);
	assert(search(0, 1, 3) == 9);
	assert(search(0, 1, 2) == 5);

	print_data();
	update(0, 0, 10);
	update(0, 1, 9);
	update(0, 2, 8);
	update(0, 3, 7);
	update(0, 4, 6);
	print_data();
	assert(search(0, 0, 4) == 40);
	assert(search(0, 0, 3) == 34);
	assert(search(0, 1, 3) == 24);
	assert(search(0, 1, 2) == 17);
}