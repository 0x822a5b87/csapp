// 统计一个数字在排序数组中出现的次数。
// 例如输入排序数组{1,2,3,3,3,3,4,5}和数字3，由于3在这个数组中出现了4次，因此输出4。
#include "iostream"
#include "vector"

typedef std::vector<int>::size_type sz;

int binary_search(std::vector<int> &nums, int target)
{
    if (nums.empty())
    {
        return 0;
    }

    long long first = 0, last = nums.size() - 1, mid;
    while (first <= last)
    {
        mid       = (last + first) / 2;
        if (nums[mid] < target)
            first = mid + 1;
        else if (nums[mid] > target)
            last = mid - 1;
        else
            return mid;
    }

    return -1;
}

int GetFirstNumberOfK(const std::vector<int> &data, int k, size_t first, size_t last)
{
    if (first > last)
    {
        return -1;
    }
    size_t mid = (first + last) / 2;
    if (mid < 0 || mid > data.size())
    {
        return -1;
    }

    if (data[mid] == k)
    {
        if (mid == 0 || data[mid - 1] != k)
        {
            return mid;
        }
        else
        {
            return GetFirstNumberOfK(data, k, first, mid - 1);
        }
    }
    else if (data[mid] > k)
    {
        return GetFirstNumberOfK(data, k, first, mid - 1);
    }
    else
    {

        return GetFirstNumberOfK(data, k, mid + 1, last);
    }
}


int GetFirstNumberOfK(const std::vector<int> &data, int k)
{
    for (size_t first = 0, last = data.size() - 1, mid = (first + last) / 2;
         mid < data.size();
         mid = (first + last) / 2)
    {
        // 其实 mid < 0 的情况不可能出现，因为 mid 是 size_t
        if (first > last || mid < 0 || mid >= data.size())
        {
            return -1;
        }

        if (data[mid] == k)
        {
            if (mid == 0 || data[mid - 1] != k)
            {
                return mid;
            }
            else
            {
                last = mid - 1;
            }
        }
        else if (data[mid] > k)
        {
            last = mid - 1;
        }
        else
        {
            first = mid + 1;
        }
    }
    return -1;
}

int GetLastNumberOfK(const std::vector<int> &data, int k, size_t first, size_t last)
{
    if (first > last)
    {
        return -1;
    }

    size_t mid = (first + last) / 2;
    if (data[mid] == k)
    {
        if (mid == data.size() || data[mid + 1] != k)
        {
            return mid;
        }
        else
        {
            return GetLastNumberOfK(data, k, mid + 1, last);
        }
    }
    else if (data[mid] > k)
    {
        return GetLastNumberOfK(data, k, first, mid - 1);
    }
    else
    {

        return GetLastNumberOfK(data, k, mid + 1, last);
    }
}

int GetNumberOfK(const std::vector<int> &data, int k)
{
    if (data.empty())
    {
        return 0;
    }

    int first = GetFirstNumberOfK(data, k);
    int last = GetLastNumberOfK(data, k, 0, data.size() - 1);

    if (first >= 0 && last >= 0)
    {
        return last - first + 1;
    }

    return 0;
}

int main(int argc, char **argv)
{
    std::vector<int> numbers{1,1,1,3,3,4,4,4,5,5,5,5,5,5,5,7};
    std::cout << GetNumberOfK(numbers, 1) << std::endl;
    std::cout << GetNumberOfK(numbers, 3) << std::endl;
    std::cout << GetNumberOfK(numbers, 4) << std::endl;
    std::cout << GetNumberOfK(numbers, 5) << std::endl;
    std::cout << GetNumberOfK(numbers, 7) << std::endl;
    std::cout << GetNumberOfK(numbers, 0) << std::endl;
    std::cout << GetNumberOfK(numbers, 10) << std::endl;
}