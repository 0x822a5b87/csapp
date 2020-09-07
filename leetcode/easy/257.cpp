//
// Created by 0x822a5b87 on 2020/9/4.
//
// 深度优先遍历

#include "iostream"
#include "vector"
#include "../ds/TreeNode.cpp"

using namespace std;

class Solution
{
public:
	vector<string> binaryTreePaths(TreeNode *root)
	{
		vector<std::string> ret;
		string              str;

		if (root == nullptr)
		{
			return ret;
		}

		dfs(ret, str, root);

		return ret;
	}

	void dfs(vector<string> &ret, string str, TreeNode *root)
	{
		// 优化：如果我们在 binaryTreePaths 中做 nullptr 判断的话，我们可以省略掉这一步
//		if (root == nullptr)
//		{
//			return;
//		}

		str.append(std::to_string(root->val));

		if (root->left == nullptr && root->right == nullptr)
		{
			ret.push_back(str);
			return;
		}

		if (root->left)
		{
			dfs(ret, str + "->", root->left);
			// 下面的这种写法其实是错误的，因为 str.append("->") 会改变 str。
			// 所以可能导致后续的解析出现错误
			// dfs(ret, str.append("->"), root->left);
		}
		if (root->right)
		{
			dfs(ret, str + "->", root->right);
		}
	}
};

/**
 * leetcode 答案
 */
class Solution2
{
public:
	vector<string> binaryTreePaths(TreeNode *root)
	{
		vector<string> res;
		if (root == nullptr) return res;

		binaryTreePaths(root, res, "");
		return res;
	}

	void binaryTreePaths(TreeNode *root, vector<string> &res, string path)
	{
		path += to_string(root->val);

		if (root->left == nullptr && root->right == nullptr)
		{
			res.push_back(path);
			return;
		}

		if (root->left) binaryTreePaths(root->left, res, path + "->");
		if (root->right) binaryTreePaths(root->right, res, path + "->");
	}
};

int main(int argc, char **argv)
{
	Solution solution;

	TreeNode node1(1);
	TreeNode node2(2);
	TreeNode node3(3);
	TreeNode node5(5);

	node1.left  = &node2;
	node1.right = &node3;
	node2.right = &node5;

	const vector<string> &ret = solution.binaryTreePaths(&node1);
	for (const auto      &str : ret)
	{
		std::cout << str << std::endl;
	}
}
