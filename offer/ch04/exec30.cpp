//
// Created by 杜航宇 on 2019-10-03.
//
// 实现一个数据结构，这个数据结构和栈一样，但是提供了 min 方法来得到栈的最小元素
// 调用 min 和 pop 和 push 的复杂度都为 O(1)

#include "iostream"
#include "StackWithMin.cpp"

/*
 * 实现的思路很简单，我们使用两个栈，一个存放实际的数据，另外一个存放当前栈的最小值
 *
 * 这里利用了栈先进先出的特性：
 * 1. 当我们入栈一个小于当前最小值的数据，我们就将它同时压入最小值栈和数据栈
 * 2. 当我们弹出一个小于当前最小值的数据时，我们将最小值栈和数据栈同时弹出
 *
 * 因为栈先进先出的特性，那么当前数据栈的最小值应该就在最小值栈的栈顶。
 */
void Test(const char* testName, const StackWithMin<int>& stack, int expected)
{
    if(testName != nullptr)
        printf("%s begins: ", testName);

    if(stack.min() == expected)
        printf("Passed.\n");
    else
        printf("Failed.\n");
}

int main(int argc, char* argv[])
{
    StackWithMin<int> stack;

    stack.push(3);
    Test("Test1", stack, 3);

    stack.push(4);
    Test("Test2", stack, 3);

    stack.push(2);
    Test("Test3", stack, 2);

    stack.push(3);
    Test("Test4", stack, 2);

    stack.pop();
    Test("Test5", stack, 2);

    stack.pop();
    Test("Test6", stack, 3);

    stack.pop();
    Test("Test7", stack, 3);

    stack.push(0);
    Test("Test8", stack, 0);

    return 0;
}

