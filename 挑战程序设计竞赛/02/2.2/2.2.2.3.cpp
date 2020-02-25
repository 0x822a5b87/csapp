#include "iostream"
#include "string"

void solve2()
{
	char        ch;
	int         num;
	std::string word, ret;

	std::cin >> num;
	while (num-- > 0)
	{
		std::cin >> ch;
		word.push_back(ch);
	}

	int head = 0, tail = word.size() - 1;
	while (head <= tail)
	{
		if (head == tail)
		{
			ret.push_back(word[head]);
			break;
		}
		else if (word[head] > word[tail])
		{
			ret.push_back(word[tail--]);
		}
		else if (word[head] < word[tail])
		{
			ret.push_back(word[head++]);
		}
		else
		{
			bool left = false;

			for (int i = 0; head + i < tail - i; i++)
			{
				if (word[head + i] < word[tail - i])
				{
					left = true;
					break;
				}
				else if (word[head + i] > word[tail - i])
				{
					left = false;
					break;
				}
			}

			if (left)
				ret.push_back(word[head++]);
			else
				ret.push_back(word[tail--]);
		}
	}

	for (int i = 0; i < ret.size(); ++i)
	{
		std::cout << ret[i];
		if (i != 0 && (i+1) % 80 == 0)
		{
			std::cout << std::endl;
		}
	}
}

int main(int argc, char **argv)
{
	solve2();
}