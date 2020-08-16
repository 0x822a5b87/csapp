//
// Created by 0x822a5b87 on 2020/8/15.
//

#include "iostream"

struct ListNode
{
	int      val;
	ListNode *next;

	explicit ListNode(int x) : val(x), next(nullptr)
	{}
};