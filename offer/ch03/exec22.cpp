//
// Created by 杜航宇 on 2019-09-29.
//
// 删除单向链表中的倒数第 k 个节点

#include "iostream"
#include "../Utilities/List.hpp"

ListNode *FindKthToTail1(ListNode *head, unsigned k)
{
    unsigned len = 0;
    ListNode *tmp = head;
    while (tmp != nullptr)
    {
        ++len;
        tmp = tmp->m_pNext;
    }
    if (len < k)
    {
        return nullptr;
    }

    unsigned index = len - k;

    while (index-- > 0)
    {
        head = head->m_pNext;
    }
    return head;
}

// 使用两个指针，我们先将后面的指针向右移动 k
// 随后开始在循环中迭代，每次循环我们都将前后两个指针移动一位，当后面的指针指向 nullptr 时，前面的指针正好移动到倒数第 k 位
ListNode *FindKthToTail(ListNode *head, unsigned k)
{
    if (head == nullptr)
    {
        return nullptr;
    }

    ListNode *prev = head, *behind = head;

    // 这里也有需要注意的问题
    // 1. i 需要声明为 unsigned 的
    // 2. 假设我们需要计算 k - 1 的话，我们一定要判断 k 是否为 0。否则由于无符号减的溢出我们会得到一个相当大的循环
    for (unsigned i = 0; i < k; ++i)
    {
        if (behind == nullptr)
        {
            return nullptr;
        }
        behind = behind->m_pNext;
    }


    // 这是最开始的代码，这里考虑漏掉了一中情况：k 正好等于链表长度的时候。这个时候 behind 正好移动到 nullptr
    // 所以我们像上面的代码，在循环中判断是否为 nullptr。

    // for (unsigned i = 0; i < k; ++i)
    // {
    //     behind = behind->m_pNext;
    // }

    // if (behind == nullptr)
    // {
    //     return nullptr;
    // }

    while (behind != nullptr)
    {
        behind = behind->m_pNext;
        prev = prev->m_pNext;
    }

    return prev;
}

// ====================测试代码====================
// 测试要找的结点在链表中间
void Test1()
{
    printf("=====Test1 starts:=====\n");
    ListNode* pNode1 = CreateListNode(1);
    ListNode* pNode2 = CreateListNode(2);
    ListNode* pNode3 = CreateListNode(3);
    ListNode* pNode4 = CreateListNode(4);
    ListNode* pNode5 = CreateListNode(5);

    ConnectListNodes(pNode1, pNode2);
    ConnectListNodes(pNode2, pNode3);
    ConnectListNodes(pNode3, pNode4);
    ConnectListNodes(pNode4, pNode5);

    printf("expected result: 4.\n");
    ListNode* pNode = FindKthToTail(pNode1, 2);
    PrintListNode(pNode);

    DestroyList(pNode1);
}

// 测试要找的结点是链表的尾结点
void Test2()
{
    printf("=====Test2 starts:=====\n");
    ListNode* pNode1 = CreateListNode(1);
    ListNode* pNode2 = CreateListNode(2);
    ListNode* pNode3 = CreateListNode(3);
    ListNode* pNode4 = CreateListNode(4);
    ListNode* pNode5 = CreateListNode(5);

    ConnectListNodes(pNode1, pNode2);
    ConnectListNodes(pNode2, pNode3);
    ConnectListNodes(pNode3, pNode4);
    ConnectListNodes(pNode4, pNode5);

    printf("expected result: 5.\n");
    ListNode* pNode = FindKthToTail(pNode1, 1);
    PrintListNode(pNode);

    DestroyList(pNode1);
}

// 测试要找的结点是链表的头结点
void Test3()
{
    printf("=====Test3 starts:=====\n");
    ListNode* pNode1 = CreateListNode(1);
    ListNode* pNode2 = CreateListNode(2);
    ListNode* pNode3 = CreateListNode(3);
    ListNode* pNode4 = CreateListNode(4);
    ListNode* pNode5 = CreateListNode(5);

    ConnectListNodes(pNode1, pNode2);
    ConnectListNodes(pNode2, pNode3);
    ConnectListNodes(pNode3, pNode4);
    ConnectListNodes(pNode4, pNode5);

    printf("expected result: 1.\n");
    ListNode* pNode = FindKthToTail(pNode1, 5);
    PrintListNode(pNode);

    DestroyList(pNode1);
}

// 测试空链表
void Test4()
{
    printf("=====Test4 starts:=====\n");
    printf("expected result: nullptr.\n");
    ListNode* pNode = FindKthToTail(nullptr, 100);
    PrintListNode(pNode);
}

// 测试输入的第二个参数大于链表的结点总数
void Test5()
{
    printf("=====Test5 starts:=====\n");
    ListNode* pNode1 = CreateListNode(1);
    ListNode* pNode2 = CreateListNode(2);
    ListNode* pNode3 = CreateListNode(3);
    ListNode* pNode4 = CreateListNode(4);
    ListNode* pNode5 = CreateListNode(5);

    ConnectListNodes(pNode1, pNode2);
    ConnectListNodes(pNode2, pNode3);
    ConnectListNodes(pNode3, pNode4);
    ConnectListNodes(pNode4, pNode5);

    printf("expected result: nullptr.\n");
    ListNode* pNode = FindKthToTail(pNode1, 6);
    PrintListNode(pNode);

    DestroyList(pNode1);
}

// 测试输入的第二个参数为0
void Test6()
{
    printf("=====Test6 starts:=====\n");
    ListNode* pNode1 = CreateListNode(1);
    ListNode* pNode2 = CreateListNode(2);
    ListNode* pNode3 = CreateListNode(3);
    ListNode* pNode4 = CreateListNode(4);
    ListNode* pNode5 = CreateListNode(5);

    ConnectListNodes(pNode1, pNode2);
    ConnectListNodes(pNode2, pNode3);
    ConnectListNodes(pNode3, pNode4);
    ConnectListNodes(pNode4, pNode5);

    printf("expected result: nullptr.\n");
    ListNode* pNode = FindKthToTail(pNode1, 0);
    PrintListNode(pNode);

    DestroyList(pNode1);
}

int main(int argc, char* argv[])
{
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
    Test6();

    return 0;
}
