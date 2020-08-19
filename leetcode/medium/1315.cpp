//
// Created by 0x822a5b87 on 2020/8/16.
//

#include "iostream"
#include "vector"
#include "../ds/TreeNode.cpp"

using namespace std;

class Solution
{
public:
	int sumEvenGrandparent(TreeNode *root)
	{
		if (root == nullptr)
		{
			return 0;
		}
		int sum = 0;
		if (root->val % 2 == 0)
		{
			sum += sumChild(root, 2);
		}

		return sum + sumEvenGrandparent(root->left) + sumEvenGrandparent(root->right);
	}

private:

	int sumChild(TreeNode *node, int d)
	{
		if (node == nullptr)
		{
			return 0;
		}

		if (d == 0)
		{
			return node->val;
		}
		else
		{
			return sumChild(node->left, d - 1) + sumChild(node->right, d - 1);
		}
	}
};