//
// Created by 杜航宇 on 2019-10-03.
//
// 二叉搜索树的后续遍历序列
// 输入一个整数数组，判断该数组是不是某个二叉树的后续遍历结果。假设输入的数字都不相同
// 左 -> 右 -> 根

#include "iostream"

/*
 * 由于后续遍历的特点，所以在整个数组中，最后的一个数字一定是根节点。并且我们能找到一个节点位置，这个位置左边均小于根节点，右边均大于根节点。
 * 因为左边的就是 BST 的左子节点，右边就是 BST 的右子节点
 *
 * 而当我们发现这个数组满足这个条件之后，我们只需要递归的去判断左子节点和右子节点是否也满足这个条件即可
 */

bool DoVerifySequenceOfBST(int sequence[], int len)
{
    if (len == 1 || len == 0)
    {
        return true;
    }

    int rootValue = sequence[len - 1];
    int cutPoint  = 0;

    for (; cutPoint != len; ++cutPoint)
    {
        // 这里必须加上等于，因为当等于的时候我们已经找到了 rootValue。这个时候说明这颗树没有右子节点
        if (sequence[cutPoint] >= rootValue)
        {
            break;
        }
    }

    // 右子树必须全部大于根节点
    for (int rightTreeIndex = cutPoint; rightTreeIndex != len; ++rightTreeIndex)
    {
        if (sequence[rightTreeIndex] < rootValue)
        {
            return false;
        }
    }

    return DoVerifySequenceOfBST(sequence, cutPoint)
           && DoVerifySequenceOfBST(sequence + cutPoint, len - cutPoint - 1);
}

bool VerifySequenceOfBST(int sequence[], int len)
{
    if (sequence == nullptr || len <= 0)
    {
        return false;
    }

    return DoVerifySequenceOfBST(sequence, len);
}

// ==================== 测试代码 ====================
void Test(const char *testName, int sequence[], int length, bool expected)
{
    if (testName != nullptr)
        printf("%s begins: ", testName);

    if (VerifySequenceOfBST(sequence, length) == expected)
        printf("passed.\n");
    else
        printf("failed.\n");
}

//            10
//         /      \
//        6        14
//       /\        /\
//      4  8     12  16
void Test1()
{
    int data[] = {4, 8, 6, 12, 16, 14, 10};
    Test("Test1", data, sizeof(data) / sizeof(int), true);
}

//           5
//          / \
//         4   7
//            /
//           6
void Test2()
{
    int data[] = {4, 6, 7, 5};
    Test("Test2", data, sizeof(data) / sizeof(int), true);
}

//               5
//              /
//             4
//            /
//           3
//          /
//         2
//        /
//       1
void Test3()
{
    int data[] = {1, 2, 3, 4, 5};
    Test("Test3", data, sizeof(data) / sizeof(int), true);
}

// 1
//  \
//   2
//    \
//     3
//      \
//       4
//        \
//         5
void Test4()
{
    int data[] = {5, 4, 3, 2, 1};
    Test("Test4", data, sizeof(data) / sizeof(int), true);
}

// 树中只有 1 个结点
void Test5()
{
    int data[] = {5};
    Test("Test5", data, sizeof(data) / sizeof(int), true);
}

void Test6()
{
    int data[] = {7, 4, 6, 5};
    Test("Test6", data, sizeof(data) / sizeof(int), false);
}

void Test7()
{
    int data[] = {4, 6, 12, 8, 16, 14, 10};
    Test("Test7", data, sizeof(data) / sizeof(int), false);
}

void Test8()
{
    Test("Test8", nullptr, 0, false);
}

int main(int argc, char *argv[])
{
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
    Test6();
    Test7();
    Test8();

    return 0;
}

