//
// Created by 0x822a5b87 on 2020/8/14.
//

#include "iostream"
#include "../ds/TreeNode.cpp"

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

class Solution
{
public:
	TreeNode *getTargetCopy(TreeNode *original, TreeNode *cloned, TreeNode *target)
	{
		if (cloned == nullptr || target == nullptr)
		{
			return nullptr;
		}

		if (cloned->val == target->val)
		{
			return cloned;
		}

		TreeNode *node = getTargetCopy(original->left, cloned->left, target);
		if (node != nullptr)
		{
			return node;
		}

		node = getTargetCopy(original->right, cloned->right, target);
		return node;
	}
};