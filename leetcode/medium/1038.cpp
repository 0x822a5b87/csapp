//
// Created by 0x822a5b87 on 2020/9/4.
//
// https://leetcode-cn.com/problems/binary-search-tree-to-greater-sum-tree/submissions/
// 如果前序遍历数组，那么得到的数组是
// 0 1 2 3 4 5 6 7  8 9
// 累加后的中序遍历就是
// 36 36 35 ...
// 对于 9，我们更新后的值是 9
// 对于 8，我们更新后的只是 9 + 8
// 那么假设我们用一个全局的 sum 变量来表示这个更新后的值，并反向中序遍历即可

#include "iostream"
#include "vector"
#include "../ds/TreeNode.cpp"

using namespace std;

class Solution
{
public:

	TreeNode *convertBST(TreeNode *root)
	{
		if (root != nullptr)
		{
			convertBST(root->right);
			sum += root->val;
			root->val = sum;
			convertBST(root->left);
		}
		return root;
	}

private:
	int sum = 0;
};

int main(int argc, char **argv)
{
	Solution solution;

	TreeNode node1(1);
	TreeNode node2(2);
	TreeNode node3(3);
	node2.left  = &node1;
	node2.right = &node3;

	solution.bstToGst(&node2);
}