//
// Created by 0x822a5b87 on 2020/8/15.
//

#include "iostream"
#include "vector"
#include "../ds/TreeNode.cpp"

using namespace std;

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
	TreeNode *constructMaximumBinaryTree(vector<int> &nums)
	{
		TreeNode       *root = nullptr;
		for (const int num : nums)
		{
			TreeNode *newNode = new TreeNode(num);
			if (root == nullptr)
			{
				root = newNode;
				continue;
			}
			else if (num > root->val)
			{
				newNode->left = root;
				root = newNode;
				continue;
			}

			TreeNode *target  = root, *parent = root;
			while (target != nullptr && target->val > num)
			{
				parent = target;
				target = target->right;
			}

			if (target == nullptr || target->val < num)
			{
				newNode->left = target;
				parent->right = newNode;
			}
			else if (target->val > num)
			{
				target->right = newNode;
			}
		}
		return root;
	}
};

int main(int argc, char **argv)
{
	vector<int> v{3, 2, 1, 6, 0, 5};
	Solution    solution;
	const auto  tree = solution.constructMaximumBinaryTree(v);
	assert(tree->val == 6);

	assert(tree->left->val == 3);
	assert(tree->left->left == nullptr);
	assert(tree->left->right->val == 2);
	assert(tree->left->right->right->val == 1);

	assert(tree->right->val == 5);
	assert(tree->right->left->val == 0);
	assert(tree->right->right == nullptr);
}