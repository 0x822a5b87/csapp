//
// Created by 杜航宇 on 2019-09-25.
//

#include "iostream"
#include "../Utilities/List.cpp"

void DeleteNode(ListNode **head, ListNode *toBeDeleted)
{
    if (toBeDeleted == nullptr || head == nullptr)
    {
        return;
    }

    std::cout << toBeDeleted->m_nValue << std::endl;
    // 删除末尾节点
    if (toBeDeleted->m_pNext == nullptr)
    {
        ListNode *current = *head;
        while (current != nullptr
               && current->m_pNext != nullptr
               && current->m_pNext->m_nValue != toBeDeleted->m_nValue)
        {
            current = current->m_pNext;
        }

        if (current != nullptr)
        {
            current->m_pNext = toBeDeleted->m_pNext;
        }

        return;
    }

    // 删除头节点

    ListNode *next = toBeDeleted->m_pNext;
    toBeDeleted->m_nValue = toBeDeleted->m_pNext->m_nValue;
    toBeDeleted->m_pNext  = toBeDeleted->m_pNext->m_pNext;
}

// ====================测试代码====================
void Test(ListNode *pListHead, ListNode *pNode)
{
    printf("The original list is: \n");
    PrintList(pListHead);

    printf("The node to be deleted is: \n");
    PrintListNode(pNode);

    DeleteNode(&pListHead, pNode);

    printf("The result list is: \n");
    PrintList(pListHead);
}

// 链表中有多个结点，删除中间的结点
void Test1()
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

    Test(pNode1, pNode3);

    DestroyList(pNode1);
}

// 链表中有多个结点，删除尾结点
void Test2()
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

    Test(pNode1, pNode5);

    DestroyList(pNode1);
}

// 链表中有多个结点，删除头结点
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

    Test(pNode1, pNode1);

    DestroyList(pNode1);
}

// 链表中只有一个结点，删除头结点
void Test4()
{
    ListNode *pNode1 = CreateListNode(1);

    Test(pNode1, pNode1);
}

// 链表为空
void Test5()
{
    Test(nullptr, nullptr);
}

int main(int argc, char *argv[])
{
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();

    return 0;
}
