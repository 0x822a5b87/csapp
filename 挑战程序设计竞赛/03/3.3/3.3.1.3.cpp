//
// Created by 0x822a5b87 on 2020/7/19.
// 线段树
// 区域修改，单点查询

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
	for (int i = 0; i < 2 * n - 1; ++i)
	{
		data[i] = tree();
		std::cin >> input[i];
	}
}

void build(int i, int l, int r)
{
	data[i].l   = l;
	data[i].r   = r;
	if (l == r)
	{
		data[i].sum = input[l];
		return;
	}
	data[i].sum = 0;

	int mid = (l + r) / 2;
	build(i * 2 + 1, l, mid);
	build(i * 2 + 2, mid + 1, r);
}

void add(int i, int l, int r, int v)
{
	// 这里的理解是错误的，因为我们可能会只增加一个点的数据
	// 不需要修改原始节点的数据
	// if (data[i].l == data[i].r)
	// {
	// 	return;
	// }

	if (l <= data[i].l && data[i].r <= r)
	{
		data[i].sum += v;
		return;
	}

	if (l <= data[i * 2 + 1].r)
	{
		add(i * 2 + 1, l, r, v);
	}
	if (data[i * 2 + 2].l <= r)
	{
		add(i * 2 + 2, l, r, v);
	}
}

int search(int i, int l, int r, int dis)
{
	if (l == r)
	{
		return data[i].sum;
	}
	if (l <= dis && dis <= r)
	{
		int mid = (l + r) / 2;
		if (dis <= mid)
		{
			const tree &node = data[i * 2 + 1];
			return data[i].sum + search(i * 2 + 1, node.l, node.r, dis);
		}
		else
		{
			const tree &node = data[i * 2 + 2];
			return data[i].sum + search(i * 2 + 2, node.l, node.r, dis);
		}
	}
	return 0;
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
	assert(search(0, 0, 4, 0) == 1);
	assert(search(0, 0, 4, 1) == 2);
	assert(search(0, 0, 4, 2) == 3);
	assert(search(0, 0, 4, 3) == 4);
	assert(search(0, 0, 4, 4) == 5);
	add(0, 0, 0, 10);
	assert(search(0, 0, 4, 0) == 11);
	add(0, 0, 1, 10);
	assert(search(0, 0, 4, 0) == 21);
	assert(search(0, 0, 4, 1) == 12);
	add(0, 0, 4, 10);
	assert(search(0, 0, 4, 0) == 31);
	assert(search(0, 0, 4, 1) == 22);
	assert(search(0, 0, 4, 2) == 13);
	assert(search(0, 0, 4, 3) == 14);
	assert(search(0, 0, 4, 4) == 15);
}