//
// Created by 杜航宇 on 2019-11-08.
//

#include "iostream"
#include "algorithm"

int FindKthMaxValue(int *arr, int len, int k)
{
    return 0;
}

/*
 * 快速排序使用分治法（Divide and conquer）策略来把一个序列（list）分为较小和较大的 2 个子序列，然后递归地排序两个子序列。
 * 步骤为：
 * 1. 挑选基准值：从数列中挑出一个元素，称为 “基准”（pivot），
 * 2. 分割：重新排序数列，所有比基准值小的元素摆放在基准前面，所有比基准值大的元素摆在基准后面（与基准值相等的数可以到任何一边）。在这个分割结束之后，对基准值的排序就已经完成，
 * 3. 递归排序子序列：递归地将小于基准值元素的子序列和大于基准值元素的子序列排序。
 *
 * 在我们的实现中，有一个原地分割算法，它分割了标示为 "左边（left）" 和 "右边（right）" 的序列部分，借由移动小于 a[pivotIndex] 的所有元素到子序列的开头，留下所有大于或等于的元素接在他们后面。
 * 在这个过程它也为基准元素找寻最后摆放的位置，也就是它回传的值。它暂时地把基准元素移到子序列的结尾，而不会被前述方式影响到。
 * 由于算法只使用交换，因此最后的数列与原先的数列拥有一样的元素。要注意的是，一个元素在到达它的最后位置前，可能会被交换很多次。
 *
 *
 * 首先选中 [4] 作为我们的 pivot
 *
 * 3  7  8 5 2  1  9 5 [4]
 *
 * 从左往右查找第一个比 4 大的数字，从右往左找到第一个比 4 小的数字。分别得到了 7 和 1
 *
 * 3 (7) 8 5 2 (1) 9 5 [4]
 *
 * 交换两个数字，增加指向前面数字的索引，减少指向后面数字的索引。继续上述过程
 *
 * 3  1  8 5 2  7  9 5 [4]
 *
 * 这次查找到的是 8 和 2
 *
 * 3  1 (8) 5 (2) 7 9 5 [4]
 *
 * 交换两个数字后我们继续上述过程
 *
 * 3 1 2 ((5)) 8 7 9 5 [4]
 * ============================
 *
 * 在我们移动的过程中，状态一定如下
 *
 * [ < pivot ] [i] [...] [j] [> pivot] [pivot]
 *
 * 因为我们的循环中 arr[i] < pivot 在前面，所以我们会先从左向右查找第一个大于 pivot 的数字，所以推出第一个循环的条件是：
 *
 * 1. arr[i] >= pivot
 *      进入第二个循环，在这个循环中，我们会从右向左查找第一个小于 pivot 的数字或者 i > j，所以退出第二个循环的条件是
 *          1.1 arr[j] <= pivot
 *              这个时候，我们直接 std::swap(arr[i], arr[j]) 并进行下一轮的循环
 *          1.2 i == j
 *              因为 i == j，交换其实没有影响。但是会导致我们退出外层循环
 * 2. arr[i] < pivot && i == j
 *      不会进入第二个循环，并且会跳出外层循环
 *
 * 可以看到我们可能因为 (1.2) 和 (2) 两种情况跳出外层循环，而这个时候 arr[i] 和 pivot 的关系是不确定的。
 * 但是 arr[i] 的左边和 arr[i] 的右边是可以确定的，他们分别小于 pivot 和 大于 pivot。
 * 如果 arr[i] > pivot，我们交换 arr[i] 和 pivot 即可达到 arr[i] 的左侧全部小于 pivot，arr[i] 的右侧全部大于 pivot
 * 对于 arr[i] < pivot，我们已经达到了了上面的那个状态。
 * 随后我们将 i + 1，并分别在剩余的两个数组中排序即可。
 */
void QuickSort(int arr[], int head, int tail)
{
    if (head >= tail)
    {
        return;
    }
    int i = head, j = tail, pivot = arr[head];
    while (i < j)
    {
        while (arr[i] <= pivot && i < j)
        {
            ++i;
        }
        while (arr[j] >= pivot && i < j)
        {
            --j;
        }
        std::swap(arr[i], arr[j]);
    }
    if (pivot > arr[i])
    {
        std::swap(arr[i], arr[head]);
    }

    QuickSort(arr, head, i - 1);
    QuickSort(arr, j + 1, tail);
}

void QuickSort(int *arr, int len)
{
    if (arr == nullptr)
    {
        return;
    }
    QuickSort(arr, 0, len - 1);
}

template<typename T>
void quick_sort_recursive(T arr[], int start, int end)
{
    if (start >= end)
    {
        return;
    }
    T   pivot = arr[end];
    int left  = start, right = end - 1;
    while (left < right)
    { //在整个范围内搜寻比枢纽元值小或大的元素，然后将左侧元素与右侧元素交换
        while (arr[left] < pivot && left < right) //试图在左侧找到一个比枢纽元更大的元素
            left++;
        while (arr[right] >= pivot && left < right) //试图在右侧找到一个比枢纽元更小的元素
            right--;
        std::swap(arr[left], arr[right]); //交换元素
    }
    if (arr[left] >= arr[end])
        std::swap(arr[left], arr[end]);
    else
        left++;
    quick_sort_recursive(arr, start, left - 1);
    quick_sort_recursive(arr, left + 1, end);
}

template<typename T>
//整數或浮點數皆可使用,若要使用物件(class)時必須設定"小於"(<)、"大於"(>)、"不小於"(>=)的運算子功能
void quick_sort(T arr[], int len)
{
    quick_sort_recursive(arr, 0, len - 1);
}


int main()
{
    int      arr0[] = {5, 1, 4, 6, 5, 3, 7};
    for (int i      = 0; i != 7; ++i)
    {
        std::cout << arr0[i] << " ";
    }
    std::cout << std::endl;
    // assert(FindKthMaxValue(arr0, 7, 1) == 9);
    // assert(FindKthMaxValue(arr0, 7, 2) == 8);
    // assert(FindKthMaxValue(arr0, 7, 3) == 7);

    QuickSort(arr0, 7);
    for (int i = 0; i != 7; ++i)
    {
        std::cout << arr0[i] << " ";
    }
}
