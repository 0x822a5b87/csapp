//
// Created by 杜航宇 on 2019-09-17.
//

#include "iostream"
#include "stack"
#include "ds/ListNode.cpp"

void PrintListReversely_Iteratively(ListNode *head)
{
    std::stack<ListNode *> nodes;
    while (head != nullptr)
    {
        nodes.push(head);
        head = head->next;
    }
    while (!nodes.empty())
    {
        head = nodes.top();
        std::cout << head->value << " ";
        nodes.pop();
    }
    std::cout << std::endl;
}

void PrintListReversely_Recursively(ListNode *head)
{
    if (head == nullptr)
    {
        std::cout << std::endl;
        return;
    }
    PrintListReversely_Recursively(head->next);
    std::cout << head->value << " ";
}


int main()
{
    ListNode *head = nullptr;

    for (int i = 0; i != 10; ++i)
    {
        AddToTail(&head, i);
    }

    PrintListReversely_Iteratively(head);
    PrintListReversely_Recursively(head);
}
