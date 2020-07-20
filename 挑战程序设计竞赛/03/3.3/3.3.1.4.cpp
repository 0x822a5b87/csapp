//
// Created by 0x822a5b87 on 2020/7/19.
// 线段树：包含 push_down

#include "iostream"

// 1. 最开始我的想法是，lazy_tag 完全只表示一个加法的值。每次在 search 的时候用
// sum + lazy_tag * len(data[i]) 来计算一个区间和
// 但是这存在一个问题，由于 push_down 的关系，我们当前区间的子区间有可能有部分值也包含了一个
// lazy_tag，用我们的方法在 search 的时候有可能会没有加到这个值

// sum 区间 [l, r] 的和
// lazy_tag 区间 [l, r] 每个元素累加的值
struct tree
{
	int l, r, sum, lazy_tag;
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
	data[i].l        = l;
	data[i].r        = r;
	data[i].lazy_tag = 0;
	if (l == r)
	{
		data[i].sum = input[l];
		return;
	}

	int mid = (l + r) / 2;
	build(i * 2 + 1, l, mid);
	build(i * 2 + 2, mid + 1, r);
	data[i].sum = data[i * 2 + 1].sum + data[i * 2 + 2].sum;
}

void push_down(int i)
{
	// 增加这个判断主要是为了性能
	if (data[i].lazy_tag != 0)
	{
		// 左右儿子加上
		data[i * 2 + 1].lazy_tag += data[i].lazy_tag;
		data[i * 2 + 2].lazy_tag += data[i].lazy_tag;

		int mid = (data[i].r + data[i].l) / 2;
		data[i * 2 + 1].sum += data[i].lazy_tag * (mid - data[i * 2 + 1].l + 1);
		data[i * 2 + 2].sum += data[i].lazy_tag * (data[i * 2 + 2].r - mid);

		data[i].lazy_tag = 0;
	}
}

void add(int i, int l, int r, int v)
{
	if (l <= data[i].l && data[i].r <= r)
	{
		data[i].sum += v * (data[i].r - data[i].l + 1);
		data[i].lazy_tag += v;
		return;
	}
	push_down(i);
	// 更新左儿子和右儿子
	if (l <= data[i * 2 + 1].r)
	{
		add(i * 2 + 1, l, r, v);
	}
	if (data[i * 2 + 2].l <= r)
	{
		add(i * 2 + 2, l, r, v);
	}
	// 更新当前节点的区间和
	data[i].sum = data[i * 2 + 1].sum + data[i * 2 + 2].sum;
}

int search(int i, int l, int r)
{
	// 如果不在区间内直接返回
	if (data[i].r < l || data[i].l > r)
	{
		return 0;
	}
	// 包含整个区间则直接返回整个区间的和
	if (l <= data[i].l && data[i].r <= r)
	{
		return data[i].sum;
	}
	// 计算左子节点和右子节点的和
	// 这里不会增加 search 的复杂度
	push_down(i);
	int s = 0;
	if (data[i * 2 + 1].r >= l)
	{
		s += search(i * 2, l, r);
	}
	if (data[i * 2 + 2].l <= r)
	{
		s += search(i * 2 + 1, l, r);
	}
	return s;
}

void print_data()
{
	std::cout << "========================" << std::endl;
	for (int i = 0; i < 2 * n - 1; ++i)
	{
		std::cout << data[i].l << " " << data[i].r << " "
				  << data[i].sum << " " << data[i].lazy_tag << std::endl;
	}
	std::cout << "========================" << std::endl;
}

int main(int argc, char **argv)
{
	init();
	build(0, 0, 4);
	assert(search(0, 0, 4) == 15);
	add(0, 0, 4, 1);
	assert(search(0, 0, 4) == 20);
	add(0, 0, 0, 10);
	assert(search(0, 0, 4) == 30);
	add(0, 4, 4, 10);
	assert(search(0, 0, 4) == 40);
	add(0, 2, 3, 10);
	assert(search(0, 0, 4) == 60);
}