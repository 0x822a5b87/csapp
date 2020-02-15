// 输入一棵二叉树的根结点，求该树的深度。
// 从根结点到叶结点依次经过的结点（含根、叶结点）形成树的一条路径，最长路径的长度为树的深度。
#include "stack"


struct TreeNode
{
    int             val;
    struct TreeNode *left;
    struct TreeNode *right;

    TreeNode(int x) :
            val(x), left(nullptr), right(nullptr)
    {
    }
};


int TreeDepth(TreeNode *pRoot)
{
    if (pRoot == nullptr)
    {
        return 0;
    }
    size_t depth = 0;
    std::deque<TreeNode*> nodeDeque;
    nodeDeque.push_front(pRoot);
    nodeDeque.push_front(nullptr);
    while (nodeDeque.back() != nullptr)
    {
        depth++;
        while (nodeDeque.back() != nullptr)
        {
            TreeNode *&node = nodeDeque.back();
            nodeDeque.pop_back();
            if (node->left != nullptr)
            {
                nodeDeque.push_front(node->left);
            }
            if (node->right != nullptr)
            {
                nodeDeque.push_front(node->right);
            }
        }
        nodeDeque.pop_back();
        nodeDeque.push_front(nullptr);
    }
    return depth;
}

int TreeDepthRecursive(TreeNode *pRoot)
{
    if (pRoot == nullptr)
    {
        return 0;
    }
    if (pRoot->left == nullptr && pRoot->right == nullptr)
    {
        return 1;
    }
    else
    {
        return 1 + std::max(TreeDepthRecursive(pRoot->left), TreeDepthRecursive(pRoot->right));
    }
}