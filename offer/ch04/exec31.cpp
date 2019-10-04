//
// Created by 杜航宇 on 2019-10-03.
//
// 栈的压入、弹出序列
// 输入两个整数序列，第一个序列表示栈的压入顺序，请判断第二个序列是否为栈的弹出序列。假设所有输入的数字均不相等
// 例如，给定 1,2,3,4,5
// 那么 [5,4,3,2,1] 和 [4,5,3,2,1] 都有可能是它的弹出序列

#include "iostream"
#include "stack"

bool IsPopOrder(const int *pushSeq, const int *popSeq, int len)
{
    if (pushSeq == nullptr || popSeq == nullptr)
    {
        return false;
    }
    std::stack<int> pushStack;
    // 1. 如果 pushStack 为空，且 pushSeq 没有取完所有元素，那么将 pushSeq 的下一个元素压入栈中
    // 2. 如果 pushStack 的栈顶和 popStack 的栈顶元素相同，那么对两个栈都执行一次 pop 操作
    // 3. 如果 pushStack 的栈顶和 popStack 的栈顶元素不同，且此时 pushSeq 还没有取完所有元素，那么将 pushSeq 的下一个元素推入栈中
    // 4. 如果 pushStack 的栈顶和 popStack 的栈顶元素不同，且此时 pushSeq 已经取完所有元素，那么程序结束返回 false
    size_t popIndex = 0;
    for (size_t pushIndex = 0; pushIndex != len;)
    {
        if (pushStack.empty())
        {
            pushStack.push(pushSeq[pushIndex++]);
            // 这里必须要 continue， 我们在每次循环中最好只修改一次 pushIndex。否则可能造成数组越界
            // 例如长度为 1 的数组，在进入循环之后首先 pushIndex++
            // 随后判断不与 popSeq[popIndex] 相等又执行一次 pushIndex++
            // 最后会造成数组越界
            continue;
        }
        if (popSeq[popIndex] == pushStack.top())
        {
            ++popIndex;
            pushStack.pop();
        }
        else
        {
            pushStack.push(pushSeq[pushIndex++]);
        }
    }

    while(!pushStack.empty())
    {
        if (pushStack.top() == popSeq[popIndex])
        {
            ++popIndex;
            pushStack.pop();
        }
        else
        {
            return false;
        }
    }

    return popIndex == len;
}

// ==================== 测试代码 ====================
void Test(const char *testName, const int *pPush, const int *pPop, int nLength, bool expected)
{
    if (testName != nullptr)
        printf("%s begins: ", testName);

    if (IsPopOrder(pPush, pPop, nLength) == expected)
        printf("Passed.\n");
    else
        printf("failed.\n");
}

void Test1()
{
    const int nLength       = 5;
    int       push[nLength] = {1, 2, 3, 4, 5};
    int       pop[nLength]  = {4, 5, 3, 2, 1};

    Test("Test1", push, pop, nLength, true);
}

void Test2()
{
    const int nLength       = 5;
    int       push[nLength] = {1, 2, 3, 4, 5};
    int       pop[nLength]  = {3, 5, 4, 2, 1};

    Test("Test2", push, pop, nLength, true);
}

void Test3()
{
    const int nLength       = 5;
    int       push[nLength] = {1, 2, 3, 4, 5};
    int       pop[nLength]  = {4, 3, 5, 1, 2};

    Test("Test3", push, pop, nLength, false);
}

void Test4()
{
    const int nLength       = 5;
    int       push[nLength] = {1, 2, 3, 4, 5};
    int       pop[nLength]  = {3, 5, 4, 1, 2};

    Test("Test4", push, pop, nLength, false);
}

// push 和 pop 序列只有一个数字
void Test5()
{
    const int nLength       = 1;
    int       push[nLength] = {1};
    int       pop[nLength]  = {2};

    Test("Test5", push, pop, nLength, false);
}

void Test6()
{
    const int nLength       = 1;
    int       push[nLength] = {1};
    int       pop[nLength]  = {1};

    Test("Test6", push, pop, nLength, true);
}

void Test7()
{
    Test("Test7", nullptr, nullptr, 0, false);
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
