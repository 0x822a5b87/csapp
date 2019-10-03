//
// Created by 杜航宇 on 2019-09-17.
//

#ifndef CSAPP_BINARYTREENODE2_HPP
#define CSAPP_BINARYTREENODE2_HPP

#include "iostream"

class BinaryTreeNode2
{
public:
    int            value;
    BinaryTreeNode2 *left;
    BinaryTreeNode2 *right;

    bool operator==(const BinaryTreeNode2 &rhs) const;

    bool operator!=(const BinaryTreeNode2 &rhs) const;

    BinaryTreeNode2();

    BinaryTreeNode2(int value, BinaryTreeNode2 *left, BinaryTreeNode2 *right);

    virtual ~BinaryTreeNode2();

private:
    bool comparePoint(const BinaryTreeNode2 *lhs, const BinaryTreeNode2 *rhs) const;
};


#endif //CSAPP_BINARYTREENODE2_HPP
