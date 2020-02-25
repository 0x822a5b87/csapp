#include <cstdio>
using namespace std;
int main()
{
	int n;
	scanf("%d", &n);
	char     a[n], ans[n];
	for (int i = 0; i < n; i++)
		scanf(" %c", &a[i]);
	int      p = 0, q = n - 1, cnt = 0;  //p、q一个指向头一个指向尾
	while (p <= q)
	{
		bool     left = true;  //是否从左边取
		for (int i    = 0; p + i < q - i; i++)
		{  //若当前字符相等，就比较下一对
			if (a[p + i] < a[q - i])
			{
				left = true;
				break;
			}
			else if (a[p + i] > a[q - i])
			{
				left = false;
				break;
			}
		}
		if (left) ans[cnt++] = a[p++];
		else ans[cnt++] = a[q--];
	}
	for (int i = 0; i < n; i++)
	{
		if (i % 80 == 0 && i != 0) printf("\n");
		printf("%c", ans[i]);
	}
	return 0;
}

