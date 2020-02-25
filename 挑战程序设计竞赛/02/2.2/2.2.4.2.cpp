// POJ 3253
// 这个问题的解法作为计算霍夫曼编码而被熟知；
#include <vector>
#include "iostream"
#include "algorithm"

int arr[20010];

int huffman(int *v, int num)
{
	std::sort(v, v + num);
	if (num == 0)
		return 0;
	else if (num == 1)
		return *v;
	else if (num == 2)
		return *v + *(v + 1);

	int sum = *v + *(v + 1);
	v = v + 1;
	*v = sum;

	return sum + huffman(v, num - 1);
}

int main(int argc, char **argv)
{
	int N, num, len = 0, i = 0;


	std::cin >> N;
	int tmp = N;
	while (tmp-- > 0)
	{
		std::cin >> num;
		len += num;
		arr[i++] = num;
	}

	std::cout << huffman(arr, N) << std::endl;
}
