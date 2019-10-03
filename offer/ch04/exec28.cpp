//
// Created by 杜航宇 on 2019-10-02.
//
// 对称的二叉树：假设一棵树的镜像和它一样，那么我们称之为对称的二叉树

#include <vector>
#include "iostream"
#include "../Utilities/BinaryTree.hpp"

/*
 * 在前面我们了解了镜像的定义，那么我们最简单的方法是先得到二叉树的镜像，然后在比较两颗二叉树是否相等
 *
 * 但是我们还有其他的方法，对于镜像来讲
 *
 * <1> root == root
 * <2> root.left = root.right
 * <3> root.left.left = root.right.right
 *
 * 那么我们可以使用前序遍历：根节点，左子节点，右子节点得到一个数组
 * 我们可以再使用一个其他的遍历方式：根节点，右子节点，左子节点得到另外一个数组
 *
 * 如果两个数组相同，那么两个二叉树就是对称的。
 *
 * 值得注意的是，相对于其他遍历，我们必须将 nullptr 也打印出来，否则会出现错误。
 */
void preOrderIter(std::vector<BinaryTreeNode *> &nodes, BinaryTreeNode *root)
{
    if (root == nullptr)
    {
        nodes.push_back(nullptr);
        return;
    }
    nodes.push_back(root);
    preOrderIter(nodes, root->m_pLeft);
    preOrderIter(nodes, root->m_pRight);
}

void reverserPreOrderIter(std::vector<BinaryTreeNode *> &nodes, BinaryTreeNode *root)
{
    if (root == nullptr)
    {
        nodes.push_back(nullptr);
        return;
    }
    nodes.push_back(root);
    reverserPreOrderIter(nodes, root->m_pRight);
    reverserPreOrderIter(nodes, root->m_pLeft);
}

bool isSymmetrical2(BinaryTreeNode *root)
{
    std::vector<BinaryTreeNode *> preOrderList, reversePreOrderList;
    preOrderIter(preOrderList, root);
    reverserPreOrderIter(reversePreOrderList, root);

    if (preOrderList.size() != reversePreOrderList.size())
    {
        return false;
    }

    for (size_t start = 0; start != preOrderList.size(); ++start)
    {
        BinaryTreeNode *&preEle        = preOrderList.at(start);
        BinaryTreeNode *&reversePreEle = reversePreOrderList.at(start);
        if (preEle == nullptr && reversePreEle == nullptr)
        {
            continue;
        }

        if ((preEle == nullptr && reversePreEle != nullptr)
            || (preEle != nullptr && reversePreEle == nullptr)
            || (preEle->m_nValue != reversePreEle->m_nValue))
        {
            return false;
        }
    }

    return true;
}

/*
 * 也可以直接不需要借助 vector，A 和 B 对称需要满足以下几个条件：
 * <1> 根节点相等
 * <2> A 的左节点和 B 的右节点对称
 * <3> A 的右节点和 A 的左节点对称
 */

bool isSymmetrical(BinaryTreeNode *root);

bool isSymmetrical(BinaryTreeNode *root, BinaryTreeNode *another);

bool isSymmetrical(BinaryTreeNode *root)
{
    return isSymmetrical(root, root);
}

bool isSymmetrical(BinaryTreeNode *root, BinaryTreeNode *another)
{
    if (root == nullptr && another == nullptr)
    {
        return true;
    }

    if (root == nullptr || another == nullptr)
    {
        return false;
    }

    return isSymmetrical(root->m_pLeft, another->m_pRight)
           && isSymmetrical(root->m_pRight, another->m_pLeft);
}

// ==================== 测试代码 ====================
void Test(char *testName, BinaryTreeNode *pRoot, bool expected)
{
    if (testName != nullptr)
        printf("%s begins: ", testName);

    if (isSymmetrical(pRoot) == expected)
        printf("Passed.\n");
    else
        printf("FAILED.\n");
}

//            8
//        6      6
//       5 7    7 5
void Test1()
{
    BinaryTreeNode *pNode8  = CreateBinaryTreeNode(8);
    BinaryTreeNode *pNode61 = CreateBinaryTreeNode(6);
    BinaryTreeNode *pNode62 = CreateBinaryTreeNode(6);
    BinaryTreeNode *pNode51 = CreateBinaryTreeNode(5);
    BinaryTreeNode *pNode71 = CreateBinaryTreeNode(7);
    BinaryTreeNode *pNode72 = CreateBinaryTreeNode(7);
    BinaryTreeNode *pNode52 = CreateBinaryTreeNode(5);

    ConnectTreeNodes(pNode8, pNode61, pNode62);
    ConnectTreeNodes(pNode61, pNode51, pNode71);
    ConnectTreeNodes(pNode62, pNode72, pNode52);

    Test("Test1", pNode8, true);

    DestroyTree(pNode8);
}

//            8
//        6      9
//       5 7    7 5
void Test2()
{
    BinaryTreeNode *pNode8  = CreateBinaryTreeNode(8);
    BinaryTreeNode *pNode61 = CreateBinaryTreeNode(6);
    BinaryTreeNode *pNode9  = CreateBinaryTreeNode(9);
    BinaryTreeNode *pNode51 = CreateBinaryTreeNode(5);
    BinaryTreeNode *pNode71 = CreateBinaryTreeNode(7);
    BinaryTreeNode *pNode72 = CreateBinaryTreeNode(7);
    BinaryTreeNode *pNode52 = CreateBinaryTreeNode(5);

    ConnectTreeNodes(pNode8, pNode61, pNode9);
    ConnectTreeNodes(pNode61, pNode51, pNode71);
    ConnectTreeNodes(pNode9, pNode72, pNode52);

    Test("Test2", pNode8, false);

    DestroyTree(pNode8);
}

//            8
//        6      6
//       5 7    7
void Test3()
{
    BinaryTreeNode *pNode8  = CreateBinaryTreeNode(8);
    BinaryTreeNode *pNode61 = CreateBinaryTreeNode(6);
    BinaryTreeNode *pNode62 = CreateBinaryTreeNode(6);
    BinaryTreeNode *pNode51 = CreateBinaryTreeNode(5);
    BinaryTreeNode *pNode71 = CreateBinaryTreeNode(7);
    BinaryTreeNode *pNode72 = CreateBinaryTreeNode(7);

    ConnectTreeNodes(pNode8, pNode61, pNode62);
    ConnectTreeNodes(pNode61, pNode51, pNode71);
    ConnectTreeNodes(pNode62, pNode72, nullptr);

    Test("Test3", pNode8, false);

    DestroyTree(pNode8);
}

//               5
//              / \
//             3   3
//            /     \
//           4       4
//          /         \
//         2           2
//        /             \
//       1               1
void Test4()
{
    BinaryTreeNode *pNode5  = CreateBinaryTreeNode(5);
    BinaryTreeNode *pNode31 = CreateBinaryTreeNode(3);
    BinaryTreeNode *pNode32 = CreateBinaryTreeNode(3);
    BinaryTreeNode *pNode41 = CreateBinaryTreeNode(4);
    BinaryTreeNode *pNode42 = CreateBinaryTreeNode(4);
    BinaryTreeNode *pNode21 = CreateBinaryTreeNode(2);
    BinaryTreeNode *pNode22 = CreateBinaryTreeNode(2);
    BinaryTreeNode *pNode11 = CreateBinaryTreeNode(1);
    BinaryTreeNode *pNode12 = CreateBinaryTreeNode(1);

    ConnectTreeNodes(pNode5, pNode31, pNode32);
    ConnectTreeNodes(pNode31, pNode41, nullptr);
    ConnectTreeNodes(pNode32, nullptr, pNode42);
    ConnectTreeNodes(pNode41, pNode21, nullptr);
    ConnectTreeNodes(pNode42, nullptr, pNode22);
    ConnectTreeNodes(pNode21, pNode11, nullptr);
    ConnectTreeNodes(pNode22, nullptr, pNode12);

    Test("Test4", pNode5, true);

    DestroyTree(pNode5);
}


//               5
//              / \
//             3   3
//            /     \
//           4       4
//          /         \
//         6           2
//        /             \
//       1               1
void Test5()
{
    BinaryTreeNode *pNode5  = CreateBinaryTreeNode(5);
    BinaryTreeNode *pNode31 = CreateBinaryTreeNode(3);
    BinaryTreeNode *pNode32 = CreateBinaryTreeNode(3);
    BinaryTreeNode *pNode41 = CreateBinaryTreeNode(4);
    BinaryTreeNode *pNode42 = CreateBinaryTreeNode(4);
    BinaryTreeNode *pNode6  = CreateBinaryTreeNode(6);
    BinaryTreeNode *pNode22 = CreateBinaryTreeNode(2);
    BinaryTreeNode *pNode11 = CreateBinaryTreeNode(1);
    BinaryTreeNode *pNode12 = CreateBinaryTreeNode(1);

    ConnectTreeNodes(pNode5, pNode31, pNode32);
    ConnectTreeNodes(pNode31, pNode41, nullptr);
    ConnectTreeNodes(pNode32, nullptr, pNode42);
    ConnectTreeNodes(pNode41, pNode6, nullptr);
    ConnectTreeNodes(pNode42, nullptr, pNode22);
    ConnectTreeNodes(pNode6, pNode11, nullptr);
    ConnectTreeNodes(pNode22, nullptr, pNode12);

    Test("Test5", pNode5, false);

    DestroyTree(pNode5);
}

//               5
//              / \
//             3   3
//            /     \
//           4       4
//          /         \
//         2           2
//                      \
//                       1
void Test6()
{
    BinaryTreeNode *pNode5  = CreateBinaryTreeNode(5);
    BinaryTreeNode *pNode31 = CreateBinaryTreeNode(3);
    BinaryTreeNode *pNode32 = CreateBinaryTreeNode(3);
    BinaryTreeNode *pNode41 = CreateBinaryTreeNode(4);
    BinaryTreeNode *pNode42 = CreateBinaryTreeNode(4);
    BinaryTreeNode *pNode21 = CreateBinaryTreeNode(2);
    BinaryTreeNode *pNode22 = CreateBinaryTreeNode(2);
    BinaryTreeNode *pNode12 = CreateBinaryTreeNode(1);

    ConnectTreeNodes(pNode5, pNode31, pNode32);
    ConnectTreeNodes(pNode31, pNode41, nullptr);
    ConnectTreeNodes(pNode32, nullptr, pNode42);
    ConnectTreeNodes(pNode41, pNode21, nullptr);
    ConnectTreeNodes(pNode42, nullptr, pNode22);
    ConnectTreeNodes(pNode21, nullptr, nullptr);
    ConnectTreeNodes(pNode22, nullptr, pNode12);

    Test("Test6", pNode5, false);

    DestroyTree(pNode5);
}

// 只有一个结点
void Test7()
{
    BinaryTreeNode *pNode1 = CreateBinaryTreeNode(1);
    Test("Test7", pNode1, true);

    DestroyTree(pNode1);
}

// 没有结点
void Test8()
{
    Test("Test8", nullptr, true);
}

// 所有结点都有相同的值，树对称
//               5
//              / \
//             5   5
//            /     \
//           5       5
//          /         \
//         5           5
void Test9()
{
    BinaryTreeNode *pNode1  = CreateBinaryTreeNode(5);
    BinaryTreeNode *pNode21 = CreateBinaryTreeNode(5);
    BinaryTreeNode *pNode22 = CreateBinaryTreeNode(5);
    BinaryTreeNode *pNode31 = CreateBinaryTreeNode(5);
    BinaryTreeNode *pNode32 = CreateBinaryTreeNode(5);
    BinaryTreeNode *pNode41 = CreateBinaryTreeNode(5);
    BinaryTreeNode *pNode42 = CreateBinaryTreeNode(5);

    ConnectTreeNodes(pNode1, pNode21, pNode22);
    ConnectTreeNodes(pNode21, pNode31, nullptr);
    ConnectTreeNodes(pNode22, nullptr, pNode32);
    ConnectTreeNodes(pNode31, pNode41, nullptr);
    ConnectTreeNodes(pNode32, nullptr, pNode42);
    ConnectTreeNodes(pNode41, nullptr, nullptr);
    ConnectTreeNodes(pNode42, nullptr, nullptr);

    Test("Test9", pNode1, true);

    DestroyTree(pNode1);
}

// 所有结点都有相同的值，树不对称
//               5
//              / \
//             5   5
//            /     \
//           5       5
//          /       /
//         5       5
void Test10()
{
    BinaryTreeNode *pNode1  = CreateBinaryTreeNode(5);
    BinaryTreeNode *pNode21 = CreateBinaryTreeNode(5);
    BinaryTreeNode *pNode22 = CreateBinaryTreeNode(5);
    BinaryTreeNode *pNode31 = CreateBinaryTreeNode(5);
    BinaryTreeNode *pNode32 = CreateBinaryTreeNode(5);
    BinaryTreeNode *pNode41 = CreateBinaryTreeNode(5);
    BinaryTreeNode *pNode42 = CreateBinaryTreeNode(5);

    ConnectTreeNodes(pNode1, pNode21, pNode22);
    ConnectTreeNodes(pNode21, pNode31, nullptr);
    ConnectTreeNodes(pNode22, nullptr, pNode32);
    ConnectTreeNodes(pNode31, pNode41, nullptr);
    ConnectTreeNodes(pNode32, pNode42, nullptr);
    ConnectTreeNodes(pNode41, nullptr, nullptr);
    ConnectTreeNodes(pNode42, nullptr, nullptr);

    Test("Test10", pNode1, false);

    DestroyTree(pNode1);
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
    Test9();
    Test10();
}
