//
// Created by 杜航宇 on 2019-09-25.
//

#ifndef CSAPP_LIST_HPP
#define CSAPP_LIST_HPP

struct ListNode
{
    int       m_nValue;
    ListNode* m_pNext;
};

ListNode* CreateListNode(int value);
void ConnectListNodes(ListNode* pCurrent, ListNode* pNext);
void PrintListNode(ListNode* pNode);
void PrintList(ListNode* pHead);
void DestroyList(ListNode* pHead);
void AddToTail(ListNode** pHead, int value);
void RemoveNode(ListNode** pHead, int value);


#endif //CSAPP_LIST_HPP
