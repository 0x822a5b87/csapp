//
// Created by 杜航宇 on 2019-10-04.
//
// 输入一颗二叉搜索树，将二叉搜索树转换成一个排序的双向链表
// 不能创建任何新的节点，只能调整树中节点指针的指向。

#include "iostream"
#include "../Utilities/BinaryTree.hpp"

/*
 * 解法二：我们也可以使用中序遍历的方法。
 */
BinaryTreeNode *Convert(BinaryTreeNode *root)
{
    if (root == nullptr)
    {
        return nullptr;
    }

    // 找到叶子节点
    if (root->m_pLeft == nullptr && root->m_pRight == nullptr)
    {
        return root;
    }

    BinaryTreeNode *left = Convert(root->m_pLeft);
    if (left != nullptr)
    {
        left->m_pRight = root;
        root->m_pLeft = left;
    }

    BinaryTreeNode *right = Convert(root->m_pRight);
    if (right != nullptr)
    {
        while (right->m_pLeft != nullptr)
        {
            right = right->m_pLeft;
        }
        root->m_pRight = right;
        right->m_pLeft = root;
    }

    return right;
}


/*
 * 根据二叉搜索树的定义，那么我们可以知道左边全是它排序链表的左边的部分，右边全是它排序列表的右边的部分。
 * 那么根据分治思想，我们只需要先将左子树转换为一个双向链表，那么我们就得到了排序链表的左半部分，同理排序列表的右半部分。
 */
BinaryTreeNode *DoConvert(BinaryTreeNode *root)
{
    if (root->m_pLeft != nullptr)
    {
        BinaryTreeNode *leftNode = DoConvert(root->m_pLeft);
        while (leftNode->m_pRight != nullptr)
        {
            leftNode = leftNode->m_pRight;
        }
        leftNode->m_pRight = root;
        root->m_pLeft  = leftNode;
    }

    if (root->m_pRight != nullptr)
    {
        BinaryTreeNode *rightNode = DoConvert(root->m_pRight);
        while (rightNode->m_pLeft != nullptr)
        {
            rightNode = rightNode->m_pLeft;
        }
        root->m_pRight = rightNode;
        rightNode->m_pLeft  = root;
    }

    return root;
}

BinaryTreeNode *Convert2(BinaryTreeNode *root)
{
    if (root == nullptr)
    {
        return nullptr;
    }
    BinaryTreeNode *node = DoConvert(root);
    while (node->m_pLeft != nullptr)
    {
        node = node->m_pLeft;
    }
    return node;
}

// ====================测试代码====================
void PrintDoubleLinkedList(BinaryTreeNode* pHeadOfList)
{
    BinaryTreeNode* pNode = pHeadOfList;

    printf("The nodes from left to right are:\n");
    while(pNode != nullptr)
    {
        printf("%d\t", pNode->m_nValue);

        if(pNode->m_pRight == nullptr)
            break;
        pNode = pNode->m_pRight;
    }

    printf("\nThe nodes from right to left are:\n");
    while(pNode != nullptr)
    {
        printf("%d\t", pNode->m_nValue);

        if(pNode->m_pLeft == nullptr)
            break;
        pNode = pNode->m_pLeft;
    }

    printf("\n");
}

void DestroyList(BinaryTreeNode* pHeadOfList)
{
    BinaryTreeNode* pNode = pHeadOfList;
    while(pNode != nullptr)
    {
        BinaryTreeNode* pNext = pNode->m_pRight;

        delete pNode;
        pNode = pNext;
    }
}

void Test(char* testName, BinaryTreeNode* pRootOfTree)
{
    if(testName != nullptr)
        printf("%s begins:\n", testName);

    PrintTree(pRootOfTree);

    BinaryTreeNode* pHeadOfList = Convert(pRootOfTree);

    PrintDoubleLinkedList(pHeadOfList);
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

    DestroyList(pNode4);
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

    DestroyList(pNode1);
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

    DestroyList(pNode1);
}

// 树中只有1个结点
void Test4()
{
    BinaryTreeNode* pNode1 = CreateBinaryTreeNode(1);
    Test("Test4", pNode1);

    DestroyList(pNode1);
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