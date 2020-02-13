// 输入两个链表，找出它们的第一个公共结点。链表结点定义如下：

// 除了这个方法之外，我们还有其他的方法来解决
// 两个链表从第一个公共节点到结束，所有的节点都是完全一致的；
// 1. 我们可以使用两个栈来辅助，先将所有的节点压入两个不同的栈；随后同时开始将两个栈弹出，最后一个相同的节点是他们第一个公共节点
// 2. 上面的方法的空间复杂度是 O(M + N)。我们可以先遍历两个链表得到两个链表的长度；随后长的那个链表先移动
//    len(M) - len(N) 步，随后两个链表同时遍历，第一个相同的节点就是链表的公共节点
#include "map"

struct ListNode
{
    int             val;
    struct ListNode *next;

    explicit ListNode(int x)
            : val(x), next(nullptr)
    {
    }
};


ListNode *FindFirstCommonNode(ListNode *pHead1, ListNode *pHead2)
{
    std::map<struct ListNode *, int> cache;
    for (ListNode *it = pHead1; it != nullptr; it = it->next)
    {
        const auto &search = cache.find(it);
        if (search == cache.end())
        {
            cache.insert({it, 1});
        }
        else
        {
            // 说明链表有循环
            break;
        }
    }

    for (ListNode *it = pHead2; it != nullptr; it = it->next)
    {
        const auto &search = cache.find(it);
        if (search != cache.end())
        {
            return search->first;
        }
    }

    return nullptr;
}


int main(int argc, char **argv)
{

}
