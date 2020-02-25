#include <vector>
#include "iostream"

void replace_adjacent(std::vector<std::vector<int>> &field,
					  size_t height, size_t width,
					  size_t i, size_t j)
{
	if (i < 0 || i >= height || j < 0 || j >= width)
		return;

	if (field[i][j] == 'W')
	{
		field[i][j] = '.';
		replace_adjacent(field, height, width, i - 1, j - 1);
		replace_adjacent(field, height, width, i, j -1);
		replace_adjacent(field, height, width, i + 1, j - 1);
		replace_adjacent(field, height, width, i - 1, j);
		replace_adjacent(field, height, width, i + 1, j);
		replace_adjacent(field, height, width, i - 1, j + 1);
		replace_adjacent(field, height, width, i, j + 1);
		replace_adjacent(field, height, width, i + 1, j + 1);
	}
}

// Lake Counting
int main(int argc, char **argv)
{
	size_t height, width;
	std::cin >> height >> width;
	std::vector<std::vector<int>> field;
	char num;
	for (size_t i = 0; i < height; ++i)
	{
		std::vector<int> v;
		field.push_back(v);
		for (size_t j = 0; j < width; ++j)
		{
			std::cin >> num;
			field[i].push_back(num);
		}
	}

	size_t lake_count = 0;

	for (size_t i = 0; i < height; ++i)
	{
		for (size_t j = 0; j < width; ++j)
		{
			if (field[i][j] == 'W')
			{
				++lake_count;
				replace_adjacent(field, height, width, i, j);
			}
		}
	}
	std::cout << lake_count << std::endl;
}