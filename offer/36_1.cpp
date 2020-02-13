// 36.cpp 其实就是归并排序的一种变体，我们可以先尝试一下实现归并排序
#include <random>
#include "iostream"
#include "vector"

typedef std::vector<int>            Arr;
typedef std::vector<int>::size_type Size;

void Merge(Arr &src, Arr &tmp, Size head, Size tail)
{
    if (head == tail)
    {
        return;
    }
    if (head == tail - 1)
    {
        if (src[head] > src[tail])
        {
            std::swap(src[head], src[tail]);
        }
        return;
    }

    Size mid = (head + tail) / 2;
    Merge(src, tmp, head, mid);
    Merge(src, tmp, mid + 1, tail);

    for (int tmpTail = tail, tmpHead = head, srcTail = tail, srcMid = mid;
         tmpTail >= tmpHead;
         )
    {
        if (src[srcMid] < src[srcTail])
        {
            tmp[tmpTail--] = src[srcTail--];
        }
        else
        {
            tmp[tmpTail--] = src[srcMid--];
        }

        if (srcTail == mid)
        {
            while (srcMid >= tmpHead)
            {
                tmp[tmpTail--] = src[srcMid--];
            }
        }

        if (srcMid < tmpHead)
        {
            while (srcTail > mid)
            {
                tmp[tmpTail--] = src[srcTail--];
            }
        }
    }

    for (Size tmpTail = tail, tmpHead = head;
         static_cast<int>(tmpTail) >= static_cast<int>(tmpHead);
         --tmpTail)
    {
        src[tmpTail] = tmp[tmpTail];
    }
}

void MergeSort(Arr &src)
{
    if (src.empty())
    {
        return;
    }
    Arr tmp(src.size());
    Merge(src, tmp, 0, src.size() - 1);
}

int main(int argc, char **argv)
{
    std::vector<int> src;

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(1, 1000);
    src.reserve(10000);
    for (int i = 0; i < 10000; ++i)
    {
        src.push_back(dist(mt));
    }
    MergeSort(src);
    int prev = src[0];
    for (const auto &number : src)
    {
        if (number < prev)
        {
            std::cout << "error" << std::endl;
        }
    }
}
