//
// Created by 0x822a5b87 on 2020/8/16.
//

#include "iostream"
#include "vector"
#include "queue"
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

class Solution {
private:
	int maxdep = -1;
	int total = 0;

public:
	void dfs(TreeNode* node, int dep) {
		if (!node) {
			return;
		}
		if (dep > maxdep) {
			maxdep = dep;
			total = node->val;
		}
		else if (dep == maxdep) {
			total += node->val;
		}
		dfs(node->left, dep + 1);
		dfs(node->right, dep + 1);
	}

	int deepestLeavesSum(TreeNode* root) {
		dfs(root, 0);
		return total;
	}
};

int main(int argc, char **argv)
{
	TreeNode *n1 = new TreeNode{1};
	TreeNode *n2 = new TreeNode{2};
	TreeNode *n3 = new TreeNode{3};
	TreeNode *n4 = new TreeNode{4};
	TreeNode *n5 = new TreeNode{5};
	TreeNode *n6 = new TreeNode{6};
	TreeNode *n7 = new TreeNode{7};
	TreeNode *n8 = new TreeNode{8};

	n1->left = n2;
	n1->right = n3;
	n2->left = n4;
	n2->right = n5;
	n3->right = n6;
	n4->left = n7;
	n6->right = n8;

	Solution solution;

	std::cout << solution.deepestLeavesSum(n1) << std::endl;
}