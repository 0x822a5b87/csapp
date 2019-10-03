//
// Created by 杜航宇 on 2019-10-02.
//
// 树的子结构
// 给定两颗二叉树 A 和 B，判断B是否为A的子树

#include "iostream"
#include "../Utilities/BinaryTree.cpp"

/*
 * 最简单的是用递归来实现。
 */
bool compareTree(BinaryTreeNode *root, BinaryTreeNode *maySubRoot)
{
    if (maySubRoot == nullptr)
    {
        return true;
    }

    if (root == nullptr && maySubRoot != nullptr)
    {
        return false;
    }

    if (root->m_nValue != maySubRoot->m_nValue)
    {
        return false;
    }

    return compareTree(root->m_pLeft, maySubRoot->m_pLeft)
           && compareTree(root->m_pRight, maySubRoot->m_pRight);
}

bool HasSubtree(BinaryTreeNode *root, BinaryTreeNode *maySubRoot)
{
    if (root == nullptr && maySubRoot != nullptr)
    {
        return false;
    }
    else if (root == nullptr && maySubRoot == nullptr)
    {
        return true;
    }
    else if (root != nullptr && maySubRoot == nullptr)
    {
        return false;
    }

    if (compareTree(root, maySubRoot))
    {
        return true;
    }

    return compareTree(root->m_pLeft, maySubRoot) || compareTree(root->m_pRight, maySubRoot);
}

// ==================== 辅助测试代码 ====================
BinaryTreeNode *CreateBinaryTreeNode(double dbValue)
{
    BinaryTreeNode *pNode = new BinaryTreeNode();
    pNode->m_nValue = dbValue;
    pNode->m_pLeft  = nullptr;
    pNode->m_pRight = nullptr;

    return pNode;
}


// ==================== 测试代码 ====================
void Test(char *testName, BinaryTreeNode *pRoot1, BinaryTreeNode *pRoot2, bool expected)
{
    if (HasSubtree(pRoot1, pRoot2) == expected)
        printf("%s passed.\n", testName);
    else
        printf("%s failed.\n", testName);
}

// 树中结点含有分叉，树 B 是树 A 的子结构
//                  8                8
//              /       \           / \
//             8         7         9   2
//           /   \
//          9     2
//               / \
//              4   7
void Test1()
{
    BinaryTreeNode *pNodeA1 = CreateBinaryTreeNode(8);
    BinaryTreeNode *pNodeA2 = CreateBinaryTreeNode(8);
    BinaryTreeNode *pNodeA3 = CreateBinaryTreeNode(7);
    BinaryTreeNode *pNodeA4 = CreateBinaryTreeNode(9);
    BinaryTreeNode *pNodeA5 = CreateBinaryTreeNode(2);
    BinaryTreeNode *pNodeA6 = CreateBinaryTreeNode(4);
    BinaryTreeNode *pNodeA7 = CreateBinaryTreeNode(7);

    ConnectTreeNodes(pNodeA1, pNodeA2, pNodeA3);
    ConnectTreeNodes(pNodeA2, pNodeA4, pNodeA5);
    ConnectTreeNodes(pNodeA5, pNodeA6, pNodeA7);

    BinaryTreeNode *pNodeB1 = CreateBinaryTreeNode(8);
    BinaryTreeNode *pNodeB2 = CreateBinaryTreeNode(9);
    BinaryTreeNode *pNodeB3 = CreateBinaryTreeNode(2);

    ConnectTreeNodes(pNodeB1, pNodeB2, pNodeB3);

    Test("Test1", pNodeA1, pNodeB1, true);

    DestroyTree(pNodeA1);
    DestroyTree(pNodeB1);
}

// 树中结点含有分叉，树 B 不是树 A 的子结构
//                  8                8
//              /       \           / \
//             8         7         9   2
//           /   \
//          9     3
//               / \
//              4   7
void Test2()
{
    BinaryTreeNode *pNodeA1 = CreateBinaryTreeNode(8);
    BinaryTreeNode *pNodeA2 = CreateBinaryTreeNode(8);
    BinaryTreeNode *pNodeA3 = CreateBinaryTreeNode(7);
    BinaryTreeNode *pNodeA4 = CreateBinaryTreeNode(9);
    BinaryTreeNode *pNodeA5 = CreateBinaryTreeNode(3);
    BinaryTreeNode *pNodeA6 = CreateBinaryTreeNode(4);
    BinaryTreeNode *pNodeA7 = CreateBinaryTreeNode(7);

    ConnectTreeNodes(pNodeA1, pNodeA2, pNodeA3);
    ConnectTreeNodes(pNodeA2, pNodeA4, pNodeA5);
    ConnectTreeNodes(pNodeA5, pNodeA6, pNodeA7);

    BinaryTreeNode *pNodeB1 = CreateBinaryTreeNode(8);
    BinaryTreeNode *pNodeB2 = CreateBinaryTreeNode(9);
    BinaryTreeNode *pNodeB3 = CreateBinaryTreeNode(2);

    ConnectTreeNodes(pNodeB1, pNodeB2, pNodeB3);

    Test("Test2", pNodeA1, pNodeB1, false);

    DestroyTree(pNodeA1);
    DestroyTree(pNodeB1);
}

// 树中结点只有左子结点，树 B 是树 A 的子结构
//                8                  8
//              /                   /
//             8                   9
//           /                    /
//          9                    2
//         /
//        2
//       /
//      5
void Test3()
{
    BinaryTreeNode *pNodeA1 = CreateBinaryTreeNode(8);
    BinaryTreeNode *pNodeA2 = CreateBinaryTreeNode(8);
    BinaryTreeNode *pNodeA3 = CreateBinaryTreeNode(9);
    BinaryTreeNode *pNodeA4 = CreateBinaryTreeNode(2);
    BinaryTreeNode *pNodeA5 = CreateBinaryTreeNode(5);

    ConnectTreeNodes(pNodeA1, pNodeA2, nullptr);
    ConnectTreeNodes(pNodeA2, pNodeA3, nullptr);
    ConnectTreeNodes(pNodeA3, pNodeA4, nullptr);
    ConnectTreeNodes(pNodeA4, pNodeA5, nullptr);

    BinaryTreeNode *pNodeB1 = CreateBinaryTreeNode(8);
    BinaryTreeNode *pNodeB2 = CreateBinaryTreeNode(9);
    BinaryTreeNode *pNodeB3 = CreateBinaryTreeNode(2);

    ConnectTreeNodes(pNodeB1, pNodeB2, nullptr);
    ConnectTreeNodes(pNodeB2, pNodeB3, nullptr);

    Test("Test3", pNodeA1, pNodeB1, true);

    DestroyTree(pNodeA1);
    DestroyTree(pNodeB1);
}

// 树中结点只有左子结点，树 B 不是树 A 的子结构
//                8                  8
//              /                   /
//             8                   9
//           /                    /
//          9                    3
//         /
//        2
//       /
//      5
void Test4()
{
    BinaryTreeNode *pNodeA1 = CreateBinaryTreeNode(8);
    BinaryTreeNode *pNodeA2 = CreateBinaryTreeNode(8);
    BinaryTreeNode *pNodeA3 = CreateBinaryTreeNode(9);
    BinaryTreeNode *pNodeA4 = CreateBinaryTreeNode(2);
    BinaryTreeNode *pNodeA5 = CreateBinaryTreeNode(5);

    ConnectTreeNodes(pNodeA1, pNodeA2, nullptr);
    ConnectTreeNodes(pNodeA2, pNodeA3, nullptr);
    ConnectTreeNodes(pNodeA3, pNodeA4, nullptr);
    ConnectTreeNodes(pNodeA4, pNodeA5, nullptr);

    BinaryTreeNode *pNodeB1 = CreateBinaryTreeNode(8);
    BinaryTreeNode *pNodeB2 = CreateBinaryTreeNode(9);
    BinaryTreeNode *pNodeB3 = CreateBinaryTreeNode(3);

    ConnectTreeNodes(pNodeB1, pNodeB2, nullptr);
    ConnectTreeNodes(pNodeB2, pNodeB3, nullptr);

    Test("Test4", pNodeA1, pNodeB1, false);

    DestroyTree(pNodeA1);
    DestroyTree(pNodeB1);
}

// 树中结点只有右子结点，树 B 是树 A 的子结构
//       8                   8
//        \                   \
//         8                   9
//          \                   \
//           9                   2
//            \
//             2
//              \
//               5
void Test5()
{
    BinaryTreeNode *pNodeA1 = CreateBinaryTreeNode(8);
    BinaryTreeNode *pNodeA2 = CreateBinaryTreeNode(8);
    BinaryTreeNode *pNodeA3 = CreateBinaryTreeNode(9);
    BinaryTreeNode *pNodeA4 = CreateBinaryTreeNode(2);
    BinaryTreeNode *pNodeA5 = CreateBinaryTreeNode(5);

    ConnectTreeNodes(pNodeA1, nullptr, pNodeA2);
    ConnectTreeNodes(pNodeA2, nullptr, pNodeA3);
    ConnectTreeNodes(pNodeA3, nullptr, pNodeA4);
    ConnectTreeNodes(pNodeA4, nullptr, pNodeA5);

    BinaryTreeNode *pNodeB1 = CreateBinaryTreeNode(8);
    BinaryTreeNode *pNodeB2 = CreateBinaryTreeNode(9);
    BinaryTreeNode *pNodeB3 = CreateBinaryTreeNode(2);

    ConnectTreeNodes(pNodeB1, nullptr, pNodeB2);
    ConnectTreeNodes(pNodeB2, nullptr, pNodeB3);

    Test("Test5", pNodeA1, pNodeB1, true);

    DestroyTree(pNodeA1);
    DestroyTree(pNodeB1);
}

// 树 A 中结点只有右子结点，树 B 不是树 A 的子结构
//       8                   8
//        \                   \
//         8                   9
//          \                 / \
//           9               3   2
//            \
//             2
//              \
//               5
void Test6()
{
    BinaryTreeNode *pNodeA1 = CreateBinaryTreeNode(8);
    BinaryTreeNode *pNodeA2 = CreateBinaryTreeNode(8);
    BinaryTreeNode *pNodeA3 = CreateBinaryTreeNode(9);
    BinaryTreeNode *pNodeA4 = CreateBinaryTreeNode(2);
    BinaryTreeNode *pNodeA5 = CreateBinaryTreeNode(5);

    ConnectTreeNodes(pNodeA1, nullptr, pNodeA2);
    ConnectTreeNodes(pNodeA2, nullptr, pNodeA3);
    ConnectTreeNodes(pNodeA3, nullptr, pNodeA4);
    ConnectTreeNodes(pNodeA4, nullptr, pNodeA5);

    BinaryTreeNode *pNodeB1 = CreateBinaryTreeNode(8);
    BinaryTreeNode *pNodeB2 = CreateBinaryTreeNode(9);
    BinaryTreeNode *pNodeB3 = CreateBinaryTreeNode(3);
    BinaryTreeNode *pNodeB4 = CreateBinaryTreeNode(2);

    ConnectTreeNodes(pNodeB1, nullptr, pNodeB2);
    ConnectTreeNodes(pNodeB2, pNodeB3, pNodeB4);

    Test("Test6", pNodeA1, pNodeB1, false);

    DestroyTree(pNodeA1);
    DestroyTree(pNodeB1);
}

// 树 A 为空树
void Test7()
{
    BinaryTreeNode *pNodeB1 = CreateBinaryTreeNode(8);
    BinaryTreeNode *pNodeB2 = CreateBinaryTreeNode(9);
    BinaryTreeNode *pNodeB3 = CreateBinaryTreeNode(3);
    BinaryTreeNode *pNodeB4 = CreateBinaryTreeNode(2);

    ConnectTreeNodes(pNodeB1, nullptr, pNodeB2);
    ConnectTreeNodes(pNodeB2, pNodeB3, pNodeB4);

    Test("Test7", nullptr, pNodeB1, false);

    DestroyTree(pNodeB1);
}

// 树 B 为空树
void Test8()
{
    BinaryTreeNode *pNodeA1 = CreateBinaryTreeNode(8);
    BinaryTreeNode *pNodeA2 = CreateBinaryTreeNode(9);
    BinaryTreeNode *pNodeA3 = CreateBinaryTreeNode(3);
    BinaryTreeNode *pNodeA4 = CreateBinaryTreeNode(2);

    ConnectTreeNodes(pNodeA1, nullptr, pNodeA2);
    ConnectTreeNodes(pNodeA2, pNodeA3, pNodeA4);

    Test("Test8", pNodeA1, nullptr, false);

    DestroyTree(pNodeA1);
}

// 树 A 和树 B 都为空
void Test9()
{
    Test("Test9", nullptr, nullptr, true);
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

    return 0;
}
