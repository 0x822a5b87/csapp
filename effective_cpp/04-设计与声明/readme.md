# 设计与声明

## 条款18： 让接口容易被正确使用，不易被误用

1. “阻止误用” 的方法包括 **建立新类型**， **限制类型上的操作**， **束缚对象值**， **消除客户的资源管理责任**
	- 建立新类型：例如对于 Date 我们传入的不是 (int, int, int) 来表示年月日，而是 (Year, Month, Day) 来表示年月日， **而 Year，Month，Day 都是 int 的 wrapper type**
	- 消除客户的资源管理责任：不从接口返回裸指针，而是从接口返回 shared_ptr 或者其他类型的智能指针
2. 还需要记住，我们应该以 **static function 替换 Non-local static 对象**
3. 任何接口如果要求客户必须记得做某些事情，就是有着 “不正确使用” 的倾向，因为客户可能会忘记做某事；
4. shared_ptr 会引入额外的开销：
	- 占用的内存是普通指针的两倍大小，因为需要动态分配内存和删除器专属数据
	- 以 virtual 的形式调用删除器
	- 在多线程内，引用计数会有 synchronize 的开销

## 条款19： 以 pass-by-reference-to-const 替代 pass-by-value

1. 对于大部分对象 pass-by-reference-to-const 往往比 pass-by-value 的代价更小，速度更快。可以避免 pass-by-value 带来的拷贝和析构开销
	- 减少开销是 & 带来的， const 保证函数内不会对对象进行操作，让用户没有后顾之忧
2. pass-by-reference-to-const 传递参数可以避免 slicing 问题；
3. C++ 的编译器底层， reference 往往以指针的形式来实现：
	- 如果我们有一个内置对象，pass-by-value 往往比 pass-by-reference-to-const 更高效
	- 对于 STL 的迭代器和函数对象也使用，因为习惯上他们都被设计为 pass-by-value

```cpp
#include "iostream"

class Base
{
public:
    virtual void print() const
    {
        std::cout << "base print" << std::endl;
    }
};

class Derived:public Base
{
public:
    void print() const override
    {
        std::cout << "derived print" << std::endl;
    }
};

void do_print(Base base)
{
    base.print();
}

void do_print_const_ref(const Base &base)
{
    base.print();
}

int main(int argc, char **argv)
{
    Derived derived;
    do_print(derived);
    // base print
    do_print_const_ref(derived);
    // derived print
}
```

## 条款21： 永远不要返回一个 reference

1. 不论是对 local 变量的引用，对 static 变量的引用，对 heap 的变量的引用都不要返回
	- local 变量的引用是未定义的
	- static 变量线程不安全，并且 (a * b == c * d) 这种形式永远返回 true
	- heap 的变量会资源泄漏

## 条款22： declare date members private

1. 如果成员变量不是 public，客户唯一能够访问对象的方法就是通过成员函数。这意味着我们可以通过成员函数提供 `封装`
	- 假设我们存在一个 averageSpeed 可以用来计算平均速度，那么我们可以通过两种方式提供出去：一个 public 的成员变量，或者是一个 public 的成员函数
	- public 的成员变量：意味着我们的更新策略已经被定死，只能实时的一直去更新这个值
	- public 的成员函数：我们的策略可以是不同的，可以在函数调用的时候去计算，也可以是后台实时的计算，调用函数时仅仅是返回 private 的成员变量。这个对用户来讲是完全透明的
2. 使用成员函数可以让我们对成员变量的处理有更精确的控制
3. protected 相对于 public 并不具有更多的封装性

## item23: prefer non-member non-friend functions to member functions

1. non-member non-friend 函数相对于成员函数， **提供了更好的封装性**。
	- 因为 non-member non-friend 函数只能访问 public 方法，而成员函数可以访问 private 方法和 protected 方法
2. 如果某些东西被封装，它就不再可见。越多的东西被封装，越少的人可以看见他。而越少的人看见它，我们就有越大的弹性去修改它
3. 为了封装性，我们可能不想让某个函数成为某个类的成员函数，但是如果我们把这个函数放到另外一个类中作为成员函数，那和 non-member non-friend 函数也是一样的。因为其他类的访问权限和 non-member，non-friend 函数的访问权限是一样的
4. 我们可以和 C++ 标准库一样，把 non-member non-friend 函数放在同一命名空间的不同源文件下

```cpp
// webbrowser.h
// 包含了核心功能
namespace WebBrowserStuff
{
	class WebBrowser { //... };

	void clearBrowser(WebBrowserStuff &wb);
}

// webbrowserbookmarks.h
// bookmarks
namespace WebBrowserStuff
{
	// ...
}

// webbrowsercookies.h
// cookies
namespace WebBrowserStuff
{
	// ...
}
```

## item24: Declare non-member functions when type conversions should apply to all parameters

1. 如果我们需要为某个函数的所有参数(包括 this 指针指向的参数)进行类型转换，那么我们应该将这个参数声明为 non-member 函数

## item25: Consider support for a non-throwing swap

1. 对于 std::swap 的模板实现，涉及到交换对象的互相复制；所以存在部分类，例如 std::string 的实现，它可能包含了一个指针指向一个 heap 上的对象，实际上当我们 swap 这种对象时只需要交换他们的指针即可
2. 对于 <1> 提到的这种需要定制 swap 函数的类
	- 提供一个 public 的 swap 成员函数高效的交换两个对象值， **这个函数绝对不应该抛出异常**
	- 在 class 或 template 的命名空间内提供一个 **non-member swap**，并令它调用上面的 swap 成员函数
	- 如果我们正在编写一个 class(非 class template)，为我们的 class 特化 std::swap。并令它调用 swap 成员函数
	- 如果调用 swap，请确定包含一个 `using std::swap` 声明，随后不加任何 namespace 修饰符，直接通过 `swap` 来调用

### 全特化(total template specialization)

```cpp
#include "iostream"

class WidgetImpl
{
public:
    WidgetImpl(int name) : name(name)
    {}

public:
    int name;
};

class Widget
{
public:
    Widget(WidgetImpl *pImpl) : pImpl(pImpl)
    {}

    void swap(Widget &other)
    {
        std::cout << "widget member function: swap is running!" << std::endl;
        using std::swap;
        swap(pImpl, other.pImpl);
    }

    WidgetImpl *pImpl;
};

namespace std
{
    template <>
    void swap<Widget>(Widget &a, Widget &b) noexcept
    {
        std::cout << "std template<> function is running" << std::endl;
        a.swap(b);
    }
}

int main(int argc, char **argv)
{
    WidgetImpl wi1(1), wi2(2);
    Widget w1(&wi1), w2(&wi2);
    std::cout << w1.pImpl->name << " " << w2.pImpl->name << std::endl;
    std::swap(w1, w2);
    std::cout << w1.pImpl->name << " " << w2.pImpl->name << std::endl;
    //1 2
    //std template<> function is running
    //widget member function: swap is running!
    //2 1
}
```

### 偏特化(partially specialize)


