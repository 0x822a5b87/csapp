//
// Created by 杜航宇 on 2019-09-24.
//

#include "iostream"
#include "../ds/TreeNode.cpp"

class Solution {
public:
    TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {
        if (t1 == nullptr && t2 == nullptr)
        {
            return nullptr;
        }
        if (t1 == nullptr)
        {
            return t2;
        }
        if (t2 == nullptr)
        {
            return t1;
        }

        TreeNode *root = new TreeNode(t1->val + t2->val);

        root->left = mergeTrees(t1->left, t2->left);
        root->right = mergeTrees(t1->right, t2->right);

        return root;
    }
};

int main()
{

}
