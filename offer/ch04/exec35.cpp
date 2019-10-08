//
// Created by 杜航宇 on 2019-10-04.
// 请实现复杂链表的复制

#include "iostream"
#include "set"
#include "../Utilities/ComplexList.hpp"

// 我们在赋值复杂链表的过程中，我们只需要首先定义一个实例，随后递归的去克隆实例即可
// 但是链表有可能会循环，所以我们需要排除那些已经赋值过的链表
ComplexListNode *CloneNodes(ComplexListNode *head, std::set<ComplexListNode *> &copiedNode)
{
    if (head == nullptr)
    {
        return nullptr;
    }
    if (copiedNode.count(head) > 0)
    {
        return head;
    }
    copiedNode.insert(head);

    ComplexListNode *node = new ComplexListNode;
    copiedNode.insert(node);
    node->m_nValue   = head->m_nValue;
    node->m_pNext    = CloneNodes(head->m_pNext, copiedNode);
    node->m_pSibling = CloneNodes(head->m_pSibling, copiedNode);

    return head;
}

ComplexListNode *CloneNodes(ComplexListNode *head)
{
    std::set<ComplexListNode *> copiedNode;

    return CloneNodes(head, copiedNode);
}

// ====================测试代码====================
void Test(const char *testName, ComplexListNode *pHead)
{
    if (testName != nullptr)
        printf("%s begins:\n", testName);

    printf("The original list is:\n");
    PrintList(pHead);

    ComplexListNode *pClonedHead = CloneNodes(pHead);

    printf("The cloned list is:\n");
    PrintList(pClonedHead);
}

//          -----------------
//         \|/              |
//  1-------2-------3-------4-------5
//  |       |      /|\             /|\
//  --------+--------               |
//          -------------------------
void Test1()
{
    ComplexListNode *pNode1 = CreateNode(1);
    ComplexListNode *pNode2 = CreateNode(2);
    ComplexListNode *pNode3 = CreateNode(3);
    ComplexListNode *pNode4 = CreateNode(4);
    ComplexListNode *pNode5 = CreateNode(5);

    BuildNodes(pNode1, pNode2, pNode3);
    BuildNodes(pNode2, pNode3, pNode5);
    BuildNodes(pNode3, pNode4, nullptr);
    BuildNodes(pNode4, pNode5, pNode2);

    Test("Test1", pNode1);
}

// m_pSibling指向结点自身
//          -----------------
//         \|/              |
//  1-------2-------3-------4-------5
//         |       | /|\           /|\
//         |       | --             |
//         |------------------------|
void Test2()
{
    ComplexListNode *pNode1 = CreateNode(1);
    ComplexListNode *pNode2 = CreateNode(2);
    ComplexListNode *pNode3 = CreateNode(3);
    ComplexListNode *pNode4 = CreateNode(4);
    ComplexListNode *pNode5 = CreateNode(5);

    BuildNodes(pNode1, pNode2, nullptr);
    BuildNodes(pNode2, pNode3, pNode5);
    BuildNodes(pNode3, pNode4, pNode3);
    BuildNodes(pNode4, pNode5, pNode2);

    Test("Test2", pNode1);
}

// m_pSibling形成环
//          -----------------
//         \|/              |
//  1-------2-------3-------4-------5
//          |              /|\
//          |               |
//          |---------------|
void Test3()
{
    ComplexListNode *pNode1 = CreateNode(1);
    ComplexListNode *pNode2 = CreateNode(2);
    ComplexListNode *pNode3 = CreateNode(3);
    ComplexListNode *pNode4 = CreateNode(4);
    ComplexListNode *pNode5 = CreateNode(5);

    BuildNodes(pNode1, pNode2, nullptr);
    BuildNodes(pNode2, pNode3, pNode4);
    BuildNodes(pNode3, pNode4, nullptr);
    BuildNodes(pNode4, pNode5, pNode2);

    Test("Test3", pNode1);
}

// 只有一个结点
void Test4()
{
    ComplexListNode *pNode1 = CreateNode(1);
    BuildNodes(pNode1, nullptr, pNode1);

    Test("Test4", pNode1);
}

// 鲁棒性测试
void Test5()
{
    Test("Test5", nullptr);
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
