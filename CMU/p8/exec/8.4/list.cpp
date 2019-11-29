//
// Created by 杜航宇 on 2019/11/29.
//

#include "iostream"

#define le2page(le, member) \
to_struct((le), struct Page, member)

// ptr = root + offset
// 所以 root = ptr - offset
#define to_struct(ptr, type, member) \
((type *) ((char *)(ptr) - m_offset_of(type, member)))

// 计算一个结构体中某个值的偏移量
// ptr->member 对于编译器其实就等于 ptr + member_offset
// 所以这里其实得到的就是 0 + member_offset
#define m_offset_of(type, member) ((size_t)(&((type*)0)->member))

struct list_entry
{
    list_entry *next, *prev;
};

struct Page
{
    short      num;
    list_entry *num_list;
};

int main()
{
    Page page1 = {};
    page1.num_list = {};
    page1.num      = 100;

    Page *p = le2page(&page1.num_list, num_list);
    std::cout << &page1 << std::endl;
    std::cout << p << std::endl;
    assert(p->num == 100);

    std::cout << m_offset_of(struct Page, num_list) << std::endl;
}
