//
// Created by 杜航宇 on 2019-09-17.
//

#ifndef CSAPP_BINARYTREENODE_HPP
#define CSAPP_BINARYTREENODE_HPP

#include "iostream"

class BinaryTreeNode
{
public:
    int            value;
    BinaryTreeNode *left;
    BinaryTreeNode *right;

    bool operator==(const BinaryTreeNode &rhs) const;

    bool operator!=(const BinaryTreeNode &rhs) const;

    BinaryTreeNode();

    BinaryTreeNode(int value, BinaryTreeNode *left, BinaryTreeNode *right);

    virtual ~BinaryTreeNode();

private:
    bool comparePoint(const BinaryTreeNode *lhs, const BinaryTreeNode *rhs) const;
};


#endif //CSAPP_BINARYTREENODE_HPP
