//
// Created by 杜航宇 on 2019-09-17.
//

#include "BinaryTreeNode2.hpp"

void PreOrderTraversal(const BinaryTreeNode2 *root)
{
    if (root == nullptr)
    {
        return;
    }
    std::cout << root->value << " ";
    PreOrderTraversal(root->left);
    PreOrderTraversal(root->right);
}

void InOrderTraversal(const BinaryTreeNode2 *root)
{
    if (root == nullptr)
    {
        return;
    }
    InOrderTraversal(root->left);
    std::cout << root->value << " ";
    InOrderTraversal(root->right);
}

void PostOrderTraversal(const BinaryTreeNode2 *root)
{
    if (root == nullptr)
    {
        return;
    }
    PostOrderTraversal(root->left);
    PostOrderTraversal(root->right);
    std::cout << root->value << " ";
}

bool BinaryTreeNode2::operator==(const BinaryTreeNode2 &rhs) const
{
    bool cr = (value == rhs.value);
    bool cl = comparePoint(left, rhs.left);
    bool cri = comparePoint(right, rhs.right);

    std::cout << "cr = " << cr << ", cl = " << cl << ", cri = " << cri  << std::endl;

    return cr && cl && cri;
}

bool BinaryTreeNode2::operator!=(const BinaryTreeNode2 &rhs) const
{
    return !(rhs == *this);
}

BinaryTreeNode2::BinaryTreeNode2(int value, BinaryTreeNode2 *left, BinaryTreeNode2 *right) : value(value), left(left),
                                                                                         right(right)
{}

BinaryTreeNode2::BinaryTreeNode2()
{}

BinaryTreeNode2::~BinaryTreeNode2() = default;

void PrintTreeNode(const BinaryTreeNode2* pNode)
{
    if(pNode != nullptr)
    {
        printf("value of this node is: %d\n", pNode->value);

        if(pNode->left != nullptr)
            printf("value of its left child is: %d.\n", pNode->left->value);
        else
            printf("left child is nullptr.\n");

        if(pNode->right != nullptr)
            printf("value of its right child is: %d.\n", pNode->right->value);
        else
            printf("right child is nullptr.\n");
    }
    else
    {
        printf("this node is nullptr.\n");
    }

    printf("\n");
}

void PrintTree(const BinaryTreeNode2* pRoot)
{
    PrintTreeNode(pRoot);

    if(pRoot != nullptr)
    {
        if(pRoot->left != nullptr)
            PrintTree(pRoot->left);

        if(pRoot->right != nullptr)
            PrintTree(pRoot->right);
    }
}

void DestroyTree(BinaryTreeNode2* pRoot)
{
    if(pRoot != nullptr)
    {
        BinaryTreeNode2* pLeft = pRoot->left;
        BinaryTreeNode2* pRight = pRoot->right;

        delete pRoot;
        pRoot = nullptr;

        DestroyTree(pLeft);
        DestroyTree(pRight);
    }
}

bool BinaryTreeNode2::comparePoint(const BinaryTreeNode2 *lhs, const BinaryTreeNode2 *rhs) const
{
    if (lhs == nullptr && rhs == nullptr)
    {
        return true;
    }
    else if (lhs != nullptr && rhs != nullptr)
    {
        return (*lhs == *rhs);
    }
    else
    {
        return false;
    }
}

//int main()
//{
//    BinaryTreeNode2 root = {}, left = {}, right = {};
//    root.value  = 4;
//    left.value  = 2;
//    right.value = 5;
//    root.left   = &left;
//    root.right  = &right;
//
//    BinaryTreeNode2 left_left = {}, left_right = {};
//    left_left.value  = 1;
//    left_right.value = 3;
//    root.left->left  = &left_left;
//    root.left->right = &left_right;
//
//    right.left       = nullptr;
//    right.right      = nullptr;
//    left_left.left   = nullptr;
//    left_left.right  = nullptr;
//    left_right.left  = nullptr;
//    left_right.right = nullptr;
//
//    PreOrderTraversal(&root);
//    std::cout << std::endl;
//    InOrderTraversal(&root);
//    std::cout << std::endl;
//    PostOrderTraversal(&root);
//    std::cout << std::endl;
//}
