//
// Created by 0x822a5b87 on 2020/8/16.
//

#include "iostream"

using namespace std;

class Solution
{
public:
	// 假设数组的长度 n 是奇数，那么需要将所有的数字全部转换为 a[n / 2]
	// 假设数组的长度 n 是偶数，那么需要将所有
	int minOperations(int n)
	{
		int sum = 0;
		while (n > 0)
		{
			sum += n - 1;
			n -= 2;
		}
		return sum;
	}

	int minOperations2(int n)
	{
		return n * n / 4;
	}
};