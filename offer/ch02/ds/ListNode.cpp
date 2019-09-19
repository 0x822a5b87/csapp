//
// Created by 杜航宇 on 2019-09-17.
// C++ 实现链表
//

#include "iostream"

struct ListNode
{
    int      value;
    ListNode *next;
};

/**
 * 这个函数的参数是一个指针的指针，因为对于空链表，我们会修改头指针。所以我们的参数必须为引用或者是一个指针
 * @param head
 * @param value
 */
void AddToTail(ListNode **head, int value)
{
    ListNode *new_node = new ListNode;
    new_node->value = value;
    new_node->next  = nullptr;

    if (*head == nullptr)
    {
        *head = new_node;
    }
    else
    {
        ListNode *p_node = *head;
        while (p_node->next != nullptr)
        {
            p_node = p_node->next;
        }
        p_node->next = new_node;
    }
}

void RemoveNode(ListNode **head, int value)
{
    if (head == nullptr || *head == nullptr)
    {
        return;
    }

    ListNode *toBeDeleteNode = *head, *prev = *head;
    while (toBeDeleteNode != nullptr && toBeDeleteNode->value != value)
    {
        prev           = toBeDeleteNode;
        toBeDeleteNode = toBeDeleteNode->next;
    }

    // 找到了需要删除的节点
    if (toBeDeleteNode != nullptr)
    {
        if (toBeDeleteNode == *head)
        {
            *head = (*head)->next;
        }
        else
        {
            prev->next = toBeDeleteNode->next;
        }
        delete toBeDeleteNode;
    }
}

void PrintList(const ListNode *head)
{
    while (head != nullptr)
    {
        std::cout << head->value << " ";
        head = head->next;
    }
    std::cout << std::endl;
}

//int main()
//{
//    ListNode *head = nullptr;
//
//    for (int i = 0; i != 10; ++i)
//    {
//        AddToTail(&head, i);
//    }
//
//    RemoveNode(nullptr, 0);
//    PrintList(head);
//    RemoveNode(&head, 0);
//    PrintList(head);
//    RemoveNode(&head, 9);
//    PrintList(head);
//    RemoveNode(&head, 10);
//    PrintList(head);
//}
