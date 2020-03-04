#include <vector>
#include "iostream"

class BinaryHeap
{
public:
	explicit BinaryHeap()
			: nums(std::vector<int>()), current(0)
	{}

	void push(const int num)
	{
		nums.push_back(num);

		size_t c = current;
		while (c != 0)
		{
			size_t parent = (c - 1) / 2;
			// BUG：之前这里我直接比较 nums[parent] < nums[c]
			if (nums[parent] < num)
			{
				break;
			}

			// 这里没有使用 std::swap，而是简单的赋值
			nums[c] = nums[parent];
			c = parent;
		}

		// 在最后才对 nums[c] 赋值
		nums[c] = num;

		current++;
	}

	int pop()
	{
		assert(current > 0);
		--current;
		int ret = nums[0], last = nums[current];
		std::swap(nums[0], nums[current]);
		nums.erase(nums.end() - 1);
		size_t i = 0;
		while (i * 2 + 1 < current)
		{
			size_t left = i * 2 + 1, right = i * 2 + 2;
			// 选择两个节点中较小的那个节点交换
			if (right < current && nums[right] < nums[left])
				left = right;

			if (nums[left] >= last)
				break;

			nums[i] = nums[left];
			i = left;
		}

		nums[i] = last;

		return ret;
	}

	size_t           current;
	std::vector<int> nums;
};

int main(int argc, char **argv)
{
	BinaryHeap heap;

	size_t      cnt = 1000;
	for (size_t i   = cnt; i != 0; --i)
		heap.push(i);

	int current = -1, prev = -1;
	for (size_t i = cnt; i != 0; --i)
	{
		prev = current;
		current = heap.pop();
		assert(current > prev);
	}
}