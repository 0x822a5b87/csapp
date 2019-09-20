//
// Created by 杜航宇 on 2019-09-19.
// 给定一颗二叉树和其中一个节点，找出中序遍历的下一个节点
// 树中的节点除了有两个分别指向左、右子节点的指针，还有一个指向父节点的指针

#include "iostream"

struct BinaryTreeNode
{
    int            value;
    BinaryTreeNode *left;
    BinaryTreeNode *right;
    BinaryTreeNode *parent;
};

// 普通二叉树
//              1
//           /     \
//          2       3
//         /       / \
//        4       5   6
//         \         /
//          7       8
//
// {4, 7, 2, 1, 5, 3, 8, 6}

// 1. 如果一个节点有右子树，那么它的下一个节点就是右子树中的最左子节点
// 2. 如果节点是父节点的左子节点，那么它的下一个节点就是父节点
// 3. 如果一个节点既没有右子树，并且还是它父节点的右子节点，那么：
//      3.1 如果它的父节点是一个左子节点，那么它的下一个节点是父节点的父节点
//      3.2 如果它的父节点是一个右子节点，那么它的下一个节点是 nullptr
// 3. 如果一个节点既没有右子树，并且还是它父节点的右子节点：那么我们遍历它的父节点，直到找到某一个节点
// 这个节点是一个左子节点，那么它的下一个节点是找到的这个节点的父节点。如果找不到这个节点，那么它的下一个节点为 nullptr

bool isLeftNode(BinaryTreeNode *node)
{
    return node != nullptr
           && node->parent != nullptr
           && node == node->parent->left;
}

bool isRightNode(BinaryTreeNode *node)
{
    return node != nullptr
           && node->parent != nullptr
           && node == node->parent->right;
}

BinaryTreeNode *GetNext(BinaryTreeNode *node)
{
    if (node == nullptr)
    {
        return nullptr;
    }
    else if (node->right != nullptr)
    {
        BinaryTreeNode *result = node->right;
        while (result->left != nullptr)
        {
            result = result->left;
        }
        return result;
    }
    else if (isLeftNode(node))
    {
        return node->parent;
    }
    else
    {
        BinaryTreeNode *parent = node;
        while ((parent = parent->parent) != nullptr)
        {
            if (isLeftNode(parent))
            {
                return parent->parent;
            }
        }
    }

    return nullptr;
}

BinaryTreeNode *GetNextPro(BinaryTreeNode *node)
{
    if (node == nullptr)
    {
        return nullptr;
    }

    // node != nullptr
    if (node->right != nullptr)
    {
        BinaryTreeNode *result = node->right;
        while (result->left != nullptr)
        {
            result = result->left;
        }
        return result;
    }

    // node != nullptr && node.right == nullptr
    if (isLeftNode(node))
    {
        return node->parent;
    }


    // node != nullptr
    // && node.right == nullptr
    // && !isLeftNode(node)
    BinaryTreeNode *parent = node;
    while ((parent = parent->parent) != nullptr)
    {
        if (isLeftNode(parent))
        {
            return parent->parent;
        }
    }

    return nullptr;
}


// ==================== 辅助代码用来构建二叉树 ====================
BinaryTreeNode *CreateBinaryTreeNode(int value)
{
    BinaryTreeNode *pNode = new BinaryTreeNode();
    pNode->value  = value;
    pNode->left   = nullptr;
    pNode->right  = nullptr;
    pNode->parent = nullptr;

    return pNode;
}

void ConnectTreeNodes(BinaryTreeNode *pParent, BinaryTreeNode *pLeft, BinaryTreeNode *pRight)
{
    if (pParent != nullptr)
    {
        pParent->left  = pLeft;
        pParent->right = pRight;

        if (pLeft != nullptr)
            pLeft->parent  = pParent;
        if (pRight != nullptr)
            pRight->parent = pParent;
    }
}

void PrintTreeNode(BinaryTreeNode *pNode)
{
    if (pNode != nullptr)
    {
        printf("value of this node is: %d\n", pNode->value);

        if (pNode->left != nullptr)
            printf("value of its left child is: %d.\n", pNode->left->value);
        else
            printf("left child is null.\n");

        if (pNode->right != nullptr)
            printf("value of its right child is: %d.\n", pNode->right->value);
        else
            printf("right child is null.\n");
    }
    else
    {
        printf("this node is null.\n");
    }

    printf("\n");
}

void PrintTree(BinaryTreeNode *pRoot)
{
    PrintTreeNode(pRoot);

    if (pRoot != nullptr)
    {
        if (pRoot->left != nullptr)
            PrintTree(pRoot->left);

        if (pRoot->right != nullptr)
            PrintTree(pRoot->right);
    }
}

void DestroyTree(BinaryTreeNode *pRoot)
{
    if (pRoot != nullptr)
    {
        BinaryTreeNode *pLeft  = pRoot->left;
        BinaryTreeNode *pRight = pRoot->right;

        delete pRoot;
        pRoot = nullptr;

        DestroyTree(pLeft);
        DestroyTree(pRight);
    }
}

// ==================== 测试代码 ====================
void Test(char *testName, BinaryTreeNode *pNode, BinaryTreeNode *expected)
{
    if (testName != nullptr)
        printf("%s begins: ", testName);

    BinaryTreeNode *pNext = GetNext(pNode);
    if (pNext == expected)
        printf("Passed.\n");
    else
        printf("FAILED.\n");
}

//            8
//        6      10
//       5 7    9  11
void Test1_7()
{
    BinaryTreeNode *pNode8  = CreateBinaryTreeNode(8);
    BinaryTreeNode *pNode6  = CreateBinaryTreeNode(6);
    BinaryTreeNode *pNode10 = CreateBinaryTreeNode(10);
    BinaryTreeNode *pNode5  = CreateBinaryTreeNode(5);
    BinaryTreeNode *pNode7  = CreateBinaryTreeNode(7);
    BinaryTreeNode *pNode9  = CreateBinaryTreeNode(9);
    BinaryTreeNode *pNode11 = CreateBinaryTreeNode(11);

    ConnectTreeNodes(pNode8, pNode6, pNode10);
    ConnectTreeNodes(pNode6, pNode5, pNode7);
    ConnectTreeNodes(pNode10, pNode9, pNode11);

    Test("Test1", pNode8, pNode9);
    Test("Test2", pNode6, pNode7);
    Test("Test3", pNode10, pNode11);
    Test("Test4", pNode5, pNode6);
    Test("Test5", pNode7, pNode8);
    Test("Test6", pNode9, pNode10);
    Test("Test7", pNode11, nullptr);

    DestroyTree(pNode8);
}

//            5
//          4
//        3
//      2
void Test8_11()
{
    BinaryTreeNode *pNode5 = CreateBinaryTreeNode(5);
    BinaryTreeNode *pNode4 = CreateBinaryTreeNode(4);
    BinaryTreeNode *pNode3 = CreateBinaryTreeNode(3);
    BinaryTreeNode *pNode2 = CreateBinaryTreeNode(2);

    ConnectTreeNodes(pNode5, pNode4, nullptr);
    ConnectTreeNodes(pNode4, pNode3, nullptr);
    ConnectTreeNodes(pNode3, pNode2, nullptr);

    Test("Test8", pNode5, nullptr);
    Test("Test9", pNode4, pNode5);
    Test("Test10", pNode3, pNode4);
    Test("Test11", pNode2, pNode3);

    DestroyTree(pNode5);
}

//        2
//         3
//          4
//           5
void Test12_15()
{
    BinaryTreeNode *pNode2 = CreateBinaryTreeNode(2);
    BinaryTreeNode *pNode3 = CreateBinaryTreeNode(3);
    BinaryTreeNode *pNode4 = CreateBinaryTreeNode(4);
    BinaryTreeNode *pNode5 = CreateBinaryTreeNode(5);

    ConnectTreeNodes(pNode2, nullptr, pNode3);
    ConnectTreeNodes(pNode3, nullptr, pNode4);
    ConnectTreeNodes(pNode4, nullptr, pNode5);

    Test("Test12", pNode5, nullptr);
    Test("Test13", pNode4, pNode5);
    Test("Test14", pNode3, pNode4);
    Test("Test15", pNode2, pNode3);

    DestroyTree(pNode2);
}

void Test16()
{
    BinaryTreeNode *pNode5 = CreateBinaryTreeNode(5);

    Test("Test16", pNode5, nullptr);

    DestroyTree(pNode5);
}

int main(int argc, char *argv[])
{
    Test1_7();
    Test8_11();
    Test12_15();
    Test16();
}
