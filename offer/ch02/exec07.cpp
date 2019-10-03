//
// Created by 杜航宇 on 2019-09-17.

// 输入二叉树的前序遍历和中序遍历结果，重建二叉树。
//
// 前序遍历：根节点，左子节点，右子节点
// 中序遍历：左子节点，右子节点，根节点
// 假设存在这么一颗树
//              4
//            /  \
//           2    5
//          / \
//         1   3
// 前序遍历：4 2 1 3 5
// 中序遍历：1 2 3 4 5
// 我们可以观察发现
// 在前序遍历中，数据是 [4] [2 1 3] [5] 分别是根节点的 root、left、right
// 在中序遍历中，数据是 [1 2 3] [4] [5] 分别是根节点的 left、root、right
// 那么我们整个流程其实可以分为三步
// 1. 用前序遍历的 root 在 中序遍历中查找
// 2. 用查找到的数字来分割，那么左边的就是左子树，右边的是右子树。并且均为中序遍历
// 3. 随后我们同样也可以确定左子树的前序遍历和右子树的前序遍历。
// 4. 我们对左节点的前序遍历和中序遍历递归调用方法，就得到了左子树，对有节点的前序遍历和中序遍历调用该方法，就得到了右子树


#include "iostream"
#include "ds/BinaryTreeNode2.cpp"


BinaryTreeNode2 *do_construct(int *preOrderBegin, int *preOrderEnd,
                             int *inOrderBegin, int *inOrderEnd)
{
    // 当只有一个数字时，那么我们无需再递归，因为它就是二叉树的根节点
    // 有一个必然的规律是，当 preOrderBegin == preOrderEnd 时
    // inOrderBegin == inOrderEnd 也必然成立
    if (preOrderBegin == preOrderEnd)
    {
        return new BinaryTreeNode2(*preOrderBegin, nullptr, nullptr);
    }
    else if (preOrderBegin > preOrderEnd)
    {
        return nullptr;
    }

    int *preOrderRoot = preOrderBegin;
    int *inOrderRoot  = inOrderBegin;
    int root_value    = *preOrderBegin;
    // 找到中序遍历中的根节点
    while (*inOrderRoot != root_value)
    {
        ++inOrderRoot;
    }

    int len = inOrderRoot - inOrderBegin;
    BinaryTreeNode2 *left  = do_construct(preOrderRoot + 1, preOrderRoot + len, inOrderBegin, inOrderRoot - 1);
    BinaryTreeNode2 *right = do_construct(preOrderRoot + len + 1, preOrderEnd, inOrderRoot + 1, inOrderEnd);

    return new BinaryTreeNode2(root_value, left, right);
}

BinaryTreeNode2 *construct(int preOrder[], int inOrder[], int length)
{
    if (preOrder == nullptr || inOrder == nullptr)
    {
        return {};
    }

    return do_construct(preOrder, preOrder + length - 1, inOrder, inOrder + length - 1);
}

// ==================== 测试代码 ====================
void Test(char *testName, int *preorder, int *inorder, int length)
{
    if (testName != nullptr)
        printf("%s begins:\n", testName);

    printf("The preorder sequence is: ");
    for (int i = 0; i < length; ++i)
        printf("%d ", preorder[i]);
    printf("\n");

    printf("The inorder sequence is: ");
    for (int i = 0; i < length; ++i)
        printf("%d ", inorder[i]);
    printf("\n");

    try
    {
        BinaryTreeNode2 *root = construct(preorder, inorder, length);
        PreOrderTraversal(root);
        std::cout << std::endl;
        InOrderTraversal(root);
        std::cout << std::endl;
        DestroyTree(root);
    }
    catch (std::exception &exception)
    {
        printf("Invalid Input.\n");
    }
}

// 普通二叉树
//              1
//           /     \
//          2       3
//         /       / \
//        4       5   6
//         \         /
//          7       8
void Test1()
{
    const int length = 8;

    int preorder[length] = {1, 2, 4, 7, 3, 5, 6, 8};
    int inorder[length]  = {4, 7, 2, 1, 5, 3, 8, 6};

    Test("Test1", preorder, inorder, length);
}

// 所有结点都没有右子结点
//            1
//           /
//          2
//         /
//        3
//       /
//      4
//     /
//    5
void Test2()
{
    const int length           = 5;
    int       preorder[length] = {1, 2, 3, 4, 5};
    int       inorder[length]  = {5, 4, 3, 2, 1};

    Test("Test2", preorder, inorder, length);
}

// 所有结点都没有左子结点
//            1
//             \
//              2
//               \
//                3
//                 \
//                  4
//                   \
//                    5
void Test3()
{
    const int length           = 5;
    int       preorder[length] = {1, 2, 3, 4, 5};
    int       inorder[length]  = {1, 2, 3, 4, 5};

    Test("Test3", preorder, inorder, length);
}

// 树中只有一个结点
void Test4()
{
    const int length           = 1;
    int       preorder[length] = {1};
    int       inorder[length]  = {1};

    Test("Test4", preorder, inorder, length);
}

// 完全二叉树
//              1
//           /     \
//          2       3
//         / \     / \
//        4   5   6   7
void Test5()
{
    const int length           = 7;
    int       preorder[length] = {1, 2, 4, 5, 3, 6, 7};
    int       inorder[length]  = {4, 2, 5, 1, 6, 3, 7};

    Test("Test5", preorder, inorder, length);
}

// 输入空指针
void Test6()
{
    Test("Test6", nullptr, nullptr, 0);
}

// 输入的两个序列不匹配
void Test7()
{
    const int length           = 7;
    int       preorder[length] = {1, 2, 4, 5, 3, 6, 7};
    int       inorder[length]  = {4, 2, 8, 1, 6, 3, 7};

    Test("Test7: for unmatched input", preorder, inorder, length);
}

int main(int argc, char *argv[])
{
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
    Test6();
    Test7();

    return 0;
}

//int main()
//{
//    BinaryTreeNode2 root = {}, left = {}, right = {};
//    root.value  = 4;
//    left.value  = 2;
//    right.value = 5;
//    root.left   = &left;
//    root.right  = &right;
//
//    BinaryTreeNode2 left_left = {}, left_right = {};
//    left_left.value  = 1;
//    left_right.value = 3;
//    root.left->left  = &left_left;
//    root.left->right = &left_right;
//
//    right.left       = nullptr;
//    right.right      = nullptr;
//    left_left.left   = nullptr;
//    left_left.right  = nullptr;
//    left_right.left  = nullptr;
//    left_right.right = nullptr;
//
//    int pre_order[5] = {4, 2, 1, 3, 5};
//    int in_order[5]  = {1, 2, 3, 4, 5};
//
//    BinaryTreeNode2 *node = construct(pre_order, in_order, 5);
//
//    PreOrderTraversal(node);
//    std::cout << std::endl;
//    InOrderTraversal(node);
//    std::cout << std::endl;
//    PreOrderTraversal(&root);
//    std::cout << std::endl;
//    InOrderTraversal(&root);
//    std::cout << std::endl;
//
//    std::cout << (*node == root) << std::endl;
//}
