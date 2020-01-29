# 实现

## item26: Postpone variable definitions as long as possible

1. 尽可能的延迟变量的定义时间以避免对象的 构造/析构开销
2. 尽量 “在直接构造时指定初值” 而不是 “调用默认构造器构造对象随后给对象赋值”

## item27: minimize casting

### 转型的几种形式

1. C 风格转型：`(T) expression`
2. 函数风格的转型动作 `T(expression)`
3. C++ 风格的四种转型

```c
#include "iostream"

class Widget
{
public:
    int x;
    int y;
    int z;

    Widget(int a, int b, int c)
    :x(a), y(b), z(c)
    {

    }
};

int main(int argc, char **argv)
{
	// 函数风格的转型，看起来好像调用了一次构造器
    const Widget &w = Widget(1, 2, 3);

    std::cout << w.x << " " << w.y << " " << w.z << std::endl;
}
```

### C++ 风格的四种新式转型

1. const_cast<T> (expression)
	- 通常用来将 const T 转换为 T
2. dynamic_cast<T> (expression)
	- 主要用来执行 “安全向下转型”，可以用来将一个基类转换为它的派生类
3. static_cast<T> (expression)
	- 强制转型，无法将 const 转换为 non-const
4. reinterpret_cast 执行低级转型，实际动作可能取决于编译器，不可移植；

```cpp
#include "iostream"

class Widget
{
public:
    int x;
    int y;
    int z;

    Widget(int a, int b, int c)
    :x(a), y(b), z(c)
    {

    }

    // 虚构造器不能少，否则不是多态的。那么不允许执行 dynamic_cast
    virtual ~Widget()
    {
        std::cout << "destructor is called" << std::endl;
    }
};

class Derived:public Widget
{
public:
    Derived(int a, int b, int c)
    :Widget(a, b, c)
    {}
};

class NotDerived
{
public:
    virtual ~NotDerived(){};
};

int main(int argc, char **argv)
{
//    const Widget &w = Widget(1, 2, 3);
//
//    std::cout << w.x << " x" << w.y << " " << w.z << std::endl;

    Widget *w1 = new Derived(1, 2, 3);
    NotDerived *nw = new NotDerived;

    if (Derived *dp = dynamic_cast<Derived*>(w1))
    {
        std::cout << "cast Widget* to Derived* successfully" << std::endl;
    }
    else
    {
        std::cout << "cast Widget* to Derived* fail" << std::endl;
    }

    if (Derived *dp = dynamic_cast<Derived*>(nw))
    {
        std::cout << "cast NotDerived* to Derived* successfully" << std::endl;
    }
    else
    {
        std::cout << "cast NotDerived* to Derived* fail" << std::endl;
    }

    delete w1;
    delete nw;

	// cast Widget* to Derived* successfully
	// cast NotDerived* to Derived* fail
	// destructor is called
}
```

---

1. 在 C++ 中，单个对象可能有多个地址；例如对于一个 Derived 对象，Base* 和 Derived* 的地址可能不一样
2. dynamic_cast 的执行速度非常慢，很多的实现包括了字符串比较

## item28: Avoid returning "handles" to object internals 

1. `handles` 表示 reference、指针或者迭代器
2. 如果我们返回一个 handles 指向对象的内部对象，那么可能：
	- 破坏封装性：假设这个内部对象是 private，那么我们的外部对象是可以通过函数来得到返回的 handles 来修改内部对象
	- 空悬 handles：当我们取得一个 handles，有可能内部的对象已经被析构了而我们的 handles 仍然还存在。这个和指向一个作用域的内部的局部对象类似。

## item29: strive for exception-safe code

1. 异常安全有两个条件
	- 不泄露任何资源：这个可以通过 shared_ptr, auto_ptr(RAII) 来保证
	- 不允许数据破坏：例如，我们修改 `bgImg = new Image(imgSrc)` 时，如果 Image 抛出异常，那么 bgImg 就被破坏了
2. 异常安全函数提供以下三种级别的保证：
	- 基本承诺：如果异常被抛出，程序内的任何事物仍然保持在有效状态下
	- 强烈保证：如果异常被抛出，那么函数就好像没有被调用过一样；这个类似于数据库的事务，一旦失败了就会回滚
	- 没有异常：保证函数总能完成他们的功能。作用于内置类型身上所有的操作都提供 nothrow 保证
3. 在保证异常安全中，有一个较好的策略：不要为了表示某件事的发生而改变对象状态，除非它真的改变了。
	- 例如假设我们的对象包含了 bgImg 和 imageChanges 两个状态，而修改 bgImg = new Image() 可能会抛出异常
	- 我们应该先调用 bgImg = new Image()，再调用 imageChanges++；因为对内置类型的操作可以保证 noexcept

### copy and swap 保证异常安全

1. copy and swap：如果我们有一个可能会抛出异常的方法和一个可能修改的对象。当我们使用方法修改这个对象时
	- 复制需要修改的对象 obj，得到副本 tmp
	- 调用可能抛出异常的方法修改 tmp
	- 如果调用未抛出异常，那么 swap(obj, tmp)

```cpp
struct PMImpl
{
	std::shared_ptr<Image> bgImage;
	int imageChanges;
};

class PrettyMenu
{
private:
	Mutex mutex;
	std::shared_ptr<PMImpl> pImpl;
};

void PrettyMenu::changeBackgroud(std::istream& imgSrc)
{
	using std::swap;
	Lock ml(&mutex);
	std::shared_ptr<PMImpl> pNew(new PMImpl(*pImpl));
	pNew->bgImage.reset(new Image(imgSrc));
	++pNew->imageChanges;
	swap(pImpl, pNew);
}
```

## item30: Understand the ins and outs of inlining

1. inline 函数是 “将函数的每一次调用” 替换为 “函数本体”。
	- 当 “函数本体” 大于 “函数的每一次调用” 时，inline 函数会增加目标代码的大小
	- 反之，inline 函数会减少目标代码的大小
2. inline 仅仅是一个申请，编译器可以忽略这个申请
3. 构造函数和析构函数往往不应该被设置为 inline 的。简单来说，因为构造函数一定会调用成员变量的构造和基类的构造函数，而如果将这些调用都进行 inline 处理的话会使得目标代码膨胀得很厉害
4. **inline 函数无法随着程序库的升级而升级**，普通的函数可能通过重新连接，如果是动态链接库甚至连重新连接都没有必要，就可以被升级到新版本。而内联函数必须被全部重新编译。
5. 一个程序往往使用 80% 的时间执行 20% 的代码，我们的优化应该集中精力到查找这 20% 的代码并优化他们。
