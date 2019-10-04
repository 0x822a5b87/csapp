//
// Created by 杜航宇 on 2019-10-03.
//
// 不分行从上到下打印二叉树，例如对于二叉树
//       8
//    /    \
//   6     10
//  / \   /  \
// 5   7 9    11
// 打印结果为 [8, 6, 10, 5, 7, 9, 11]

#include <stack>
#include "iostream"
#include "../Utilities/BinaryTree.hpp"

void PrintFromTopToBottom(BinaryTreeNode *root)
{
    if (root == nullptr)
    {
        return;
    }
    std::stack<BinaryTreeNode *> currentRound, nextRound;
    currentRound.push(root);
    while (!currentRound.empty())
    {
        while (!currentRound.empty())
        {
            BinaryTreeNode *&node = currentRound.top();
            currentRound.pop();
            std::cout << node->m_nValue << " ";
            if (node->m_pLeft != nullptr)
            {
                nextRound.push(node->m_pLeft);
            }
            if (node->m_pRight != nullptr)
            {
                nextRound.push(node->m_pRight);
            }
        }

        while (!nextRound.empty())
        {
            BinaryTreeNode *&node = nextRound.top();
            nextRound.pop();
            currentRound.push(node);
        }
    }
}

void PrintFromTopToBottomSplitLine(BinaryTreeNode *root)
{
    if (root == nullptr)
    {
        return;
    }
    std::stack<BinaryTreeNode *> currentRound, nextRound;
    currentRound.push(root);
    while (!currentRound.empty())
    {
        while (!currentRound.empty())
        {
            BinaryTreeNode *&node = currentRound.top();
            currentRound.pop();
            std::cout << node->m_nValue << " ";
            if (node->m_pLeft != nullptr)
            {
                nextRound.push(node->m_pLeft);
            }
            if (node->m_pRight != nullptr)
            {
                nextRound.push(node->m_pRight);
            }
        }

        std::cout << std::endl;

        while (!nextRound.empty())
        {
            BinaryTreeNode *&node = nextRound.top();
            nextRound.pop();
            currentRound.push(node);
        }
    }
}

// ==================== 测试代码 ====================
void Test(char* testName, BinaryTreeNode* pRoot)
{
    if(testName != nullptr)
        printf("%s begins: \n", testName);

    PrintTree(pRoot);

    printf("The nodes from top to bottom, from left to right are: \n");
    PrintFromTopToBottom(pRoot);

    printf("\n\n");
}

//            10
//         /      \
//        6        14
//       /\        /\
//      4  8     12  16
void Test1()
{
    BinaryTreeNode* pNode10 = CreateBinaryTreeNode(10);
    BinaryTreeNode* pNode6 = CreateBinaryTreeNode(6);
    BinaryTreeNode* pNode14 = CreateBinaryTreeNode(14);
    BinaryTreeNode* pNode4 = CreateBinaryTreeNode(4);
    BinaryTreeNode* pNode8 = CreateBinaryTreeNode(8);
    BinaryTreeNode* pNode12 = CreateBinaryTreeNode(12);
    BinaryTreeNode* pNode16 = CreateBinaryTreeNode(16);

    ConnectTreeNodes(pNode10, pNode6, pNode14);
    ConnectTreeNodes(pNode6, pNode4, pNode8);
    ConnectTreeNodes(pNode14, pNode12, pNode16);

    Test("Test1", pNode10);

    DestroyTree(pNode10);
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
void Test2()
{
    BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);
    BinaryTreeNode* pNode4 = CreateBinaryTreeNode(4);
    BinaryTreeNode* pNode3 = CreateBinaryTreeNode(3);
    BinaryTreeNode* pNode2 = CreateBinaryTreeNode(2);
    BinaryTreeNode* pNode1 = CreateBinaryTreeNode(1);

    ConnectTreeNodes(pNode5, pNode4, nullptr);
    ConnectTreeNodes(pNode4, pNode3, nullptr);
    ConnectTreeNodes(pNode3, pNode2, nullptr);
    ConnectTreeNodes(pNode2, pNode1, nullptr);

    Test("Test2", pNode5);

    DestroyTree(pNode5);
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
void Test3()
{
    BinaryTreeNode* pNode1 = CreateBinaryTreeNode(1);
    BinaryTreeNode* pNode2 = CreateBinaryTreeNode(2);
    BinaryTreeNode* pNode3 = CreateBinaryTreeNode(3);
    BinaryTreeNode* pNode4 = CreateBinaryTreeNode(4);
    BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);

    ConnectTreeNodes(pNode1, nullptr, pNode2);
    ConnectTreeNodes(pNode2, nullptr, pNode3);
    ConnectTreeNodes(pNode3, nullptr, pNode4);
    ConnectTreeNodes(pNode4, nullptr, pNode5);

    Test("Test3", pNode1);

    DestroyTree(pNode1);
}

// 树中只有 1 个结点
void Test4()
{
    BinaryTreeNode* pNode1 = CreateBinaryTreeNode(1);
    Test("Test4", pNode1);

    DestroyTree(pNode1);
}

// 树中没有结点
void Test5()
{
    Test("Test5", nullptr);
}

int main(int argc, char* argv[])
{
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();

    return 0;
}