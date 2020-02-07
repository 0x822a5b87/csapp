#include "iostream"
#include "vector"

bool CheckMoreThanHalf(const std::vector<int> &numbers, int num)
{
    long cnt = std::count_if(std::begin(numbers), std::end(numbers),
                             [=](int number) -> bool
                             {
                                 return num == number;
                             });

    return (2 * cnt) > numbers.size();
}


int MoreThanHalfNum(std::vector<int> &arr, size_t head, size_t tail)
{
    if (head >= tail)
        return 0;
    size_t i = head, j = tail;
    int pivot = arr[head];

    while (i < j)
    {
        while (i < j && arr[i] <= pivot)
        {
            ++i;
        }
        while (i < j && arr[j] >= pivot)
        {
            --j;
        }

        std::swap(arr[i], arr[j]);
    }
    if (arr[head] > arr[i])
    {
        std::swap(arr[head], arr[i]);
    }

    MoreThanHalfNum(arr, head, i - 1);
    MoreThanHalfNum(arr, j + 1, tail);

    return 0;
}

int MoreThanHalfNum(std::vector<int> &numbers)
{
    return MoreThanHalfNum(numbers, 0, numbers.size() - 1);
}

int MoreThanHalfNum_Solution(std::vector<int> numbers)
{
    if (numbers.empty())
    {
        return 0;
    }
    else if (numbers.size() == 1)
    {
        return numbers[0];
    }
    else
    {
        return MoreThanHalfNum(numbers);
    }
}

int main(int argc, char **argv)
{
    std::vector<int> numbers{3,2,2,3,2,4,2,5,2,3,2};
    std::cout << MoreThanHalfNum_Solution(numbers) << std::endl;

    std::for_each(std::begin(numbers), std::end(numbers),
                  [](int num) -> void {
                      std::cout << num << " ";
                  });
    std::cout << std::endl;
    MoreThanHalfNum(numbers);
    std::for_each(std::begin(numbers), std::end(numbers),
            [](int num) -> void {
                std::cout << num << " ";
            });
    std::cout << std::endl;
}
