# 资源管理

## 条款13： 以对象管理资源

1. 我们可以使用 shared_ptr 或者 auto_ptr 来实现 RAII
2. shared_ptr 和 auto_ptr 在析构函数内调用 delete 而非 delete[]

## 条款14： 在资源管理类中小心 copying 行为

```cpp
void lock(Mutex *pm);
void unlock(Mutex *pm);

class Lock
{
public:
	explicit Lock(Mutex *pm)
	: mutexPtr(pm)
	{
		lock(mutexPtr);
	}
	~Lock()
	{
		unlock(mutexPtr);
	}
private:
	Mutex *mutexPtr;
};
```

1. 上面的符合 RAII，但是存在一个问题：当我们对 Lock 对象进行 copying 时会发生什么？我们有两种策略：
	- 禁止复制：通过前面的条款可知
	- 对底层资源使用 “引用计数”：可以使用 shared_ptr 来实现

```cpp
class Lock
{
public:
	explicit Lock(Mutex *pm)
	// 使用 unlock 作为删除器代替 shared_ptr 默认的 delete 操作
	: mutexPtr(pm, unlock)
	{
		lock(mutexPtr.get());
	}
private:
	std::shared_ptr<Mutex> mutexPtr;
};
```

---

```cpp
#include "iostream"

class Widget
{
public:
    explicit Widget()
            : Widget(std::string("default"))
    {}

    explicit Widget(const std::string &name)
    :theName(name)
    {
        increment_id();
        std::cout << "default constructor is called, name == " << name
                  << ", id == " << id << std::endl;
    }

    ~Widget()
    {
        std::cout << "destructor is called, name == " << theName
                  << ",id = " << id << std::endl;
    }

    Widget(const Widget &w)
    {
        increment_id();
        std::cout << "copy constructor is called" << std::endl;
    }

    Widget &operator=(const Widget &rhs)
    {
        increment_id();
        std::cout << "copy assignment is called" << std::endl;
        return *this;
    }

private:
    static int id;
    std::string theName;

    static void increment_id()
    {
        ++id;
    }
};

int Widget::id = 0;

int main(int argc, char **argv)
{
    auto                    *w = new Widget("w1");
    std::unique_ptr<Widget> ptr(w);

    w = new Widget("w2");
    std::shared_ptr<Widget> sptr(w, [](Widget *wptr)
    {
        std::cout << "customized deleter is called!" << std::endl;
        delete wptr;
    });
}
// default constructor is called, name == w1, id == 1
// default constructor is called, name == w2, id == 2
// customized deleter is called!
// destructor is called, name == w2,id = 2
// destructor is called, name == w1,id = 2
```

## 条款15： 在资源管理类中提供对原始资源的访问

1. 不论底层我们使用 shared_ptr 还是 auto_ptr 来管理资源，我们都必须提供对原始资源的管理：
	- 可以通过智能指针的 get() 方法来实现
	- 可以通过重载 () 来实现
	- shared_ptr 和 auto_ptr 都重载了 `operator->` 和 `operator*`，也可以通过他们来访问

## 条款16： 使用 new 和 delete 时要采用相同的形式

1. new 对应 delete，new [] 对应 delete[]

## 条款17： 以独立语句将 newed 对象置入智能指针

```cpp
int priority();
void processWidget(std::shared_ptr<Widget> pw, int priority);

processWidget(std::shared_ptr<Widget>(new Widget()), priority());
```

1. 上面的方法会可能会造成资源泄漏；C++ 不规定函数的参数求值顺序，所有有可能出现
	- new Widget() 执行
	- priority() 执行
2. 如果在 priority() 执行时抛出异常，那么就造成了资源泄漏
