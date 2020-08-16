//
// Created by 0x822a5b87 on 2020/8/15.
//

#include "iostream"
#include "vector"
#include "../ds/TreeNode.cpp"
#include "../ds/ListNode.cpp"

using namespace std;

class Solution
{
public:
	// 广度优先遍历即可
	vector<ListNode *> listOfDepth(TreeNode *tree)
	{
		vector<ListNode *> v;
		vector<ListNode *> last;
		bfs(v, last, tree, 0);
		return v;
	}

	void bfs(vector<ListNode *> &v, vector<ListNode *> &last,
			 TreeNode *tree, size_t d)
	{
		if (tree == nullptr)
		{
			return;
		}
		if (v.size() <= d)
		{
			v.resize(d + 1);
			last.resize(d + 1);
			ListNode *node = new ListNode(tree->val);
			v[d]    = node;
			last[d] = node;
		}
		else
		{
			ListNode *newNode = new ListNode(tree->val);
			last[d]->next = newNode;
			last[d] = newNode;
		}

		bfs(v, last, tree->left, d + 1);
		bfs(v, last, tree->right, d + 1);
	}
};

int main(int argc, char **argv)
{
	TreeNode *n1 = new TreeNode(1);
	TreeNode *n2 = new TreeNode(2);
	TreeNode *n3 = new TreeNode(3);
	TreeNode *n4 = new TreeNode(4);
	TreeNode *n5 = new TreeNode(5);
	TreeNode *n7 = new TreeNode(7);
	TreeNode *n8 = new TreeNode(8);

	n1->left = n2;
	n1->right = n3;
	n2->left = n4;
	n2->right = n5;
	n4->left = n8;
	n3->right = n7;

	Solution solution;
	const vector<ListNode *> &v = solution.listOfDepth(n1);

	for (int i = 0; i < v.size(); ++i)
	{
		ListNode *root = v[i];
		while (root != nullptr)
		{
			std::cout << root->val << " ";
			root = root->next;
		}
		std::cout  << std::endl;
	}
}