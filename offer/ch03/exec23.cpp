//
// Created by 杜航宇 on 2019-09-29.
//
// 1. 确定一个链表中是否包含环，如果包含环的找出环的入口节点。

#include "iostream"
#include "../Utilities/List.hpp"

/**
 * 整个算法的思路是：
 * 1. 假设存在一个环，那么当两个速度不一致的指针在链表上移动时，移动速度快的一定会赶上移动慢的
 * 2. 同上，假设存在一个环，那么我们现在可以这么算。
 *    假设环的长度为 n，那么我们用一个指针，这个指针先移动 n 步。随后一个指针从头开始移动当移动 k 步的时候，
 *    两个指针的位置应该分别是 k 和 k + n。也就是当两个指针会和的位置就是环的入口。
 */
ListNode *MeetingNode(ListNode *head)
{
    ListNode *quick = head, *slow = head;
    while (quick != nullptr && quick->m_pNext != nullptr)
    {
        quick = quick->m_pNext->m_pNext;
        slow  = slow->m_pNext;
        if (quick == slow)
        {
            return quick;
        }
    }
    return nullptr;
}

ListNode *EntryNodeOfLoop(ListNode *head)
{
    ListNode *meetingNode = MeetingNode(head);
    if (meetingNode == nullptr)
    {
        return nullptr;
    }

    ListNode *quick  = meetingNode, *slow = meetingNode;
    ListNode *behind = head, *prev = head;
    /**
     * 将 behind 指针向后移动 n， n 是环的长度
     */
    do
    {
        behind = behind->m_pNext;
        quick  = quick->m_pNext->m_pNext;
        slow   = slow->m_pNext;
    } while (quick != slow);

    while (prev != behind)
    {
        prev   = prev->m_pNext;
        behind = behind->m_pNext;
    }

    return behind;
}

// ==================== Test Code ====================
void Test(char *testName, ListNode *pHead, ListNode *entryNode)
{
    if (testName != nullptr)
        printf("%s begins: ", testName);

    if (EntryNodeOfLoop(pHead) == entryNode)
        printf("Passed.\n");
    else
        printf("FAILED.\n");
}

// A list has a node, without a loop
void Test1()
{
    ListNode *pNode1 = CreateListNode(1);

    Test("Test1", pNode1, nullptr);

    DestroyList(pNode1);
}

// A list has a node, with a loop
void Test2()
{
    ListNode *pNode1 = CreateListNode(1);
    ConnectListNodes(pNode1, pNode1);

    Test("Test2", pNode1, pNode1);

    delete pNode1;
    pNode1 = nullptr;
}

// A list has multiple nodes, with a loop
void Test3()
{
    ListNode *pNode1 = CreateListNode(1);
    ListNode *pNode2 = CreateListNode(2);
    ListNode *pNode3 = CreateListNode(3);
    ListNode *pNode4 = CreateListNode(4);
    ListNode *pNode5 = CreateListNode(5);

    ConnectListNodes(pNode1, pNode2);
    ConnectListNodes(pNode2, pNode3);
    ConnectListNodes(pNode3, pNode4);
    ConnectListNodes(pNode4, pNode5);
    ConnectListNodes(pNode5, pNode3);

    Test("Test3", pNode1, pNode3);

    delete pNode1;
    pNode1 = nullptr;
    delete pNode2;
    pNode2 = nullptr;
    delete pNode3;
    pNode3 = nullptr;
    delete pNode4;
    pNode4 = nullptr;
    delete pNode5;
    pNode5 = nullptr;
}

// A list has multiple nodes, with a loop
void Test4()
{
    ListNode *pNode1 = CreateListNode(1);
    ListNode *pNode2 = CreateListNode(2);
    ListNode *pNode3 = CreateListNode(3);
    ListNode *pNode4 = CreateListNode(4);
    ListNode *pNode5 = CreateListNode(5);

    ConnectListNodes(pNode1, pNode2);
    ConnectListNodes(pNode2, pNode3);
    ConnectListNodes(pNode3, pNode4);
    ConnectListNodes(pNode4, pNode5);
    ConnectListNodes(pNode5, pNode1);

    Test("Test4", pNode1, pNode1);

    delete pNode1;
    pNode1 = nullptr;
    delete pNode2;
    pNode2 = nullptr;
    delete pNode3;
    pNode3 = nullptr;
    delete pNode4;
    pNode4 = nullptr;
    delete pNode5;
    pNode5 = nullptr;
}

// A list has multiple nodes, with a loop
void Test5()
{
    ListNode *pNode1 = CreateListNode(1);
    ListNode *pNode2 = CreateListNode(2);
    ListNode *pNode3 = CreateListNode(3);
    ListNode *pNode4 = CreateListNode(4);
    ListNode *pNode5 = CreateListNode(5);

    ConnectListNodes(pNode1, pNode2);
    ConnectListNodes(pNode2, pNode3);
    ConnectListNodes(pNode3, pNode4);
    ConnectListNodes(pNode4, pNode5);
    ConnectListNodes(pNode5, pNode5);

    Test("Test5", pNode1, pNode5);

    delete pNode1;
    pNode1 = nullptr;
    delete pNode2;
    pNode2 = nullptr;
    delete pNode3;
    pNode3 = nullptr;
    delete pNode4;
    pNode4 = nullptr;
    delete pNode5;
    pNode5 = nullptr;
}

// A list has multiple nodes, without a loop
void Test6()
{
    ListNode *pNode1 = CreateListNode(1);
    ListNode *pNode2 = CreateListNode(2);
    ListNode *pNode3 = CreateListNode(3);
    ListNode *pNode4 = CreateListNode(4);
    ListNode *pNode5 = CreateListNode(5);

    ConnectListNodes(pNode1, pNode2);
    ConnectListNodes(pNode2, pNode3);
    ConnectListNodes(pNode3, pNode4);
    ConnectListNodes(pNode4, pNode5);

    Test("Test6", pNode1, nullptr);

    DestroyList(pNode1);
}

// Empty list
void Test7()
{
    Test("Test7", nullptr, nullptr);
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
