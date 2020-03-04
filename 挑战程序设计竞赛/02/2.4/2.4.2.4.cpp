#include "iostream"

class node
{
public:
	int  val;
	node *left;
	node *right;

	explicit node(int val) : val(val), left(nullptr), right(nullptr)
	{}

	virtual ~node()
	{
		// 不需要手动的删除 val
		// delete &val;
		delete left;
		left = nullptr;

		delete right;
		right = nullptr;
	}

	node *insert(node *p, int x);

	node *remove(node *p, int x);

	node *find(node *p, int);

private:

	/**
	 * 返回 p 内一个指向 x 的节点的参数
	 */
	node **find_node_in_parent(node *p, int x);
};


node *insert2(node *p, int x)
{
	if (p == nullptr)
	{
		p = new node(x);
		return p;
	}
	else
	{
		// 这里其实可以用递归
		node *n = new node(x);
		// parent_p 指向它的左子节点或者右子节点
		node **parent_p = &p, *cur = p;
		while (cur != nullptr && cur->val != n->val)
		{
			parent_p = &cur;
			if (cur->val > x)
			{
				cur = cur->left;
				parent_p = &cur->left;
			}
			else if (cur->val < x)
			{
				cur = cur->right;
				parent_p = &cur->right;
			}
			else
			{
				return p;
			}
		}

		if (*parent_p == nullptr)
		{
			*parent_p = n;
		}

		return p;
	}
}

node *node::insert(node *p, int x)
{
	if (p == nullptr)
	{
		p = new node(x);
		return p;
	}
	else
	{
		// 这里其实可以用递归
		node *n = new node(x);
		// parent_p 指向我们要插入的位置的父节点中的指针
		// 可能是 left 或者 right
		// 这样我们就可以通过修改 parent_p 来修改父节点中的指针指向当前位置了
		node **parent_p = find_node_in_parent(p, x);
		if (*parent_p == nullptr)
		{
			*parent_p = n;
		}

		return p;
	}
}

node* node::find(node *p, int x)
{
	if (!p)
	{
		return nullptr;
	}

	while (p != nullptr)
	{
		if (p->val > x)
		{
			p = p->left;
		}
		else if (p->val < x)
		{
			p = p->right;
		}
		else
		{
			return p;
		}
	}

	return nullptr;
}

node *node::remove(node *p, int x)
{
	if (p == nullptr)
		return nullptr;

	node **parent_p = find_node_in_parent(p, x);
	if (*parent_p == nullptr)
	{
		// 没有找到对应的节点
		return nullptr;
	}

	node *r = *parent_p;
	if (r->left == nullptr)
	{
		*parent_p = r->right;
	}
	else if (r->right == nullptr)
	{
		*parent_p = r->left;
	}
	else
	{
		// 找到指向左子节点中最大的那个节点的指针
		node *max_in_left = r;
		node **max_left_p = &r;
		while (max_in_left->right != nullptr)
		{
			max_left_p = &max_in_left;
			max_in_left = max_in_left->right;
		}
		// max_in_left 指向要删除的节点中的左子节点的最大节点
		// *max_left_p 指向 max_in_left 的父节点中的 right
		// r 指向需要删除的那个节点
		max_in_left->left = r->left;
		max_in_left->right = r->right;
		*parent_p = max_in_left;

		*max_left_p = nullptr;
		r->left = nullptr;
		r->right = nullptr;
		delete r;
	}
	return p;
}

node **node::find_node_in_parent(node *p, int x)
{
	node **parent_p = &p, *cur = p;
	while (cur != nullptr && cur->val != x)
	{
		if (cur->val > x)
		{
			parent_p = &cur->left;
			cur = cur->left;
		}
		else if (cur->val < x)
		{
			parent_p = &cur->right;
			cur = cur->right;
		}

	}

	return parent_p;
}

int main(int argc, char **argv)
{
	node *p = nullptr;

	for (int i = 50; i != 0; --i)
	{
		p = p->insert(p, i);
	}
	for (int i = 50; i != 0; --i)
	{
		p = p->insert(p, i);
	}

	for (int i = 100; i != 50; --i)
	{
		p = p->insert(p, i);
	}
	for (int i = 100; i != 50; --i)
	{
		p = p->insert(p, i);
	}

	for (int i = 100; i != 0; --i)
	{
		assert(p->find(p, i)->val == i);
	}

	for (int i = 200; i != 100; --i)
	{
		assert(p->find(p, i) == nullptr);
	}

	for (int i = 100; i != 50; --i)
	{
		p = p->remove(p, i);
	}

	for (int i = 100; i != 50; --i)
	{
		assert(p->find(p, i) == nullptr);
	}

	for (int i = 50; i != 0; --i)
	{
		assert(p->find(p, i)->val == i);
	}
}
