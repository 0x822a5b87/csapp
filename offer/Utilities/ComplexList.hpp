//
// Created by 杜航宇 on 2019-10-04.
//

#ifndef CSAPP_COMPLEXLIST_HPP
#define CSAPP_COMPLEXLIST_HPP


#pragma once

struct ComplexListNode
{
    int                 m_nValue;
    ComplexListNode*    m_pNext;
    ComplexListNode*    m_pSibling;
};

ComplexListNode* CreateNode(int nValue);
void BuildNodes(ComplexListNode* pNode, ComplexListNode* pNext, ComplexListNode* pSibling);
void PrintList(ComplexListNode* pHead);

#endif //CSAPP_COMPLEXLIST_HPP
