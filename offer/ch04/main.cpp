//
// Created by 杜航宇 on 2019-09-25.
//

#include <set>
#include "iostream"
#include "../Utilities/BinaryTree.hpp"

BinaryTreeNode *Convert(BinaryTreeNode *root)
{
    if (root == nullptr)
    {
        return nullptr;
    }

    std::cout << root->m_nValue << std::endl;

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

int main()
{
//    BinaryTreeNode *left_left   = CreateBinaryTreeNode(1);
//    BinaryTreeNode *left_right  = CreateBinaryTreeNode(3);
//    BinaryTreeNode *left        = CreateBinaryTreeNode(2);
    BinaryTreeNode *root        = CreateBinaryTreeNode(3);
    BinaryTreeNode *right       = CreateBinaryTreeNode(4);
    BinaryTreeNode *right_right = CreateBinaryTreeNode(5);

//    root->m_pLeft  = left;
    root->m_pRight = right;

//    left->m_pLeft  = left_left;
//    left->m_pRight = left_right;

    right->m_pRight = right_right;

    BinaryTreeNode *convertRoot = Convert(root);
    while (convertRoot != nullptr)
    {
        std::cout << convertRoot->m_nValue << std::endl;
        convertRoot = convertRoot->m_pLeft;
    }

    DestroyTree(root);
}
