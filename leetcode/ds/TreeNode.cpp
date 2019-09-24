//
// Created by 杜航宇 on 2019-09-24.
//

#include "iostream"

struct TreeNode
{
    int      val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr)
    {}
};
