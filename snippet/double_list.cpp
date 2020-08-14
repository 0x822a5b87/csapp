//
// Created by 0x822a5b87 on 2020/8/11.
//
// 在 c 语言没有模板的情况下通用的双向链表

#include "iostream"

// convert list entry to page
#define le2page(le, member) to_struct((le), struct page, member)

// Return the offset of 'member' relative to the beginning of a struct type
#define offset_of(type, member) \
((size_t)(&((type *)100)->member))

/**
 * to_struct - get a struct from a ptr
 *
 * @ptr: a struct pointer of member
 * @type: the type of the struct this is embedded in
 * @member: the name of the member within the struct
 */
#define to_struct(ptr, type, member) \
((type *)((char *)(ptr) - (offset_of(type, member) - 100)))

struct list_entry
{
	list_entry *next, *prev;
};

struct page
{
	int        value;
	list_entry page_link;
};

int main(int argc, char **argv)
{
	page p{1024, nullptr};
	std::cout << offset_of(page, page_link) << std::endl;
	// 8
	page *pt = to_struct(&p.page_link, page, page_link);
	std::cout << pt->value << std::endl;
	// 1024
}