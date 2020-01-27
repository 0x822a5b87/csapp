# 构造/析构/赋值运算

## 条款05：了解 C++ 默默编写并调用了哪些函数

1. C++ 编译器会为我们自动生成 构造函数、析构函数、copy 构造函数和 copy 赋值函数；
	- 当我们没有手动声明时编译器才会为我们构造
	- 当这些函数有被调用时才会生成
2. 编译器生成的析构函数是 `non-virtual` 的，这意味着当我们继承一个没有手动定义 virtual 析构函数的类可能会引起一些问题
3. 编译器合成的 **拷贝构造函数** 和 **拷贝赋值函数** 只是单纯的将来源对象的每个 **non-static 成员变量** 拷贝到目标对象
4. 如果存在无法通过拷贝赋值或者拷贝构造的成员变量，那么编译器无法为类合成相应的构造器
	- 引用：C++ 不允许将 reference 改指向不同的对象
	- const 变量


>在我们下面的代码中，如果不手动的声明 Item05 为虚函数，那么在我们 delete item_05 时将不会调用 Item05D 的析构函数

```cpp
#include "iostream"

class Item05
{
public:
    virtual ~Item05();
};

Item05::~Item05()
{
    std::cout << "Item05 destructor is running!" << std::endl;
}

class Item05D: public Item05
{
    ~Item05D() override
    {
        std::cout << "Item05D destructor is running!" << std::endl;
    }
};

int main(int argc, char **argv)
{
    Item05 *item_05 = new Item05D();
    delete item_05;
}
```

---

>合成的拷贝构造函数在赋值 non-static 成员变量时
><br/>
>如果是拷贝赋值，通过成员变量的拷贝赋值函数来拷贝
><br/>
>如果是拷贝构造，则通过成员变量额拷贝构造函数来拷贝

```cpp
#include "iostream"

class Test03
{
public:
    Test03()
    {
        std::cout << "constructor is running" << std::endl;
    }

    Test03(const Test03 &w)
    {
        std::cout << "copy constructor is called" << std::endl;
    }

    const Test03& operator=(const Test03& rhs)
    {
        std::cout << "copy assignment is called" << std::endl;
        return rhs;
    }
};


class Test04
{
public:
    Test04()
    {
        std::cout << "04 constructor is running" << std::endl;
    }

private:
    Test03 t;
};

int main(int argc, char **argv)
{
    Test04 t0;
    Test04 t1;

    t0 = t1;

    Test04 t2(t0);
}
// constructor is running
// 04 constructor is running
// constructor is running
// 04 constructor is running
// copy assignment is called
// copy constructor is called
```

## 条款06： 若不想使用编译器自动生成的函数，就应该明确的拒绝

1. 将 copy constructor 和 copy assignment 设置为 private，可以阻止编译器生成相应的构造器；但是这样成员函数和 friend 函数仍然可以调用它们；
2. 将 copy constructor 和 copy assignment 设置为 private 并且不实现它们，避免 <1> 提到的，因为调用它们会在连接期引起一个异常
3. 通过声明基类，并将基类的 copy constructor 和 copy assignment 设置为 private 并且不实现；随后所以继承该基类的类会无法使用编译器自动生成的 copy 函数
	- 优点：可以将报错从连接期间提前到编译期
	- 缺点：可能会有多继承使得程序变得过于复杂

## 条款07： 为多态基类声明 virtual 析构函数

1. C++ 明确指出，当 derived class 对象经由一个 base class 指针删除，而 base class 的析构函数是 non-virtual 的，那么行为是未定义的；
2. 虚函数通常是由虚函数指针实现的：每一个带有虚函数的 class 都有一个虚函数表，而当调用虚函数时，会在虚函数表中查找相应的虚函数
3. 严禁继承一个析构函数为 non-virtual 的函数，可能会导致 UB

## 条款08： 别让异常逃离析构函数

1. 对 C++ 而言，如果同时存在两个异常时，程序若不是结束执行就是导致 UB
2. 有一种设计策略，是通过某种方式，让用户可以手动的去执行某些操作，而这个操作可能会导致异常；并记录用户是否有手动的调用操作，如果没有那么在析构函数中去调用；

```cpp
class DBConn
{
public:
	void close()
	{
		// db.close 可能会抛出异常
		db.close();
		// 记录用户是否手动的调用了 close 
		closed = true;
	}

	~DBConn()
	{
		// 如果用户没有手动调用 close，那么由析构函数来确保 close 被调用
		if (!closed)
		{
		try {
			db.close();
		}
		catch(...)
		{
			// ...
		}
		}
	}

private:
	DBConnection db;
	bool closed;
};
```

## 条款09： 绝不在构造和析构函数中调用 virtual 函数

1. 在构造函数执行期间，base class 的 **virtual 函数不会下降加到 derived class**。
2. 这是很好理解的，因为在构造函数执行期间，derived class 可能还未初始化；而当执行析构函数时，derived class 因为已经执行完了 derived class 的析构函数导致所有的成员变量都失效
3. 我们无法使用 virtual 函数从 base class 向下调用，在构造期间， **可以由 derived class 将必要的构造信息向上传递至 base class 的构造函数**

## 条款10： 令 operator= 返回一个 reference to `*this`

## 条款11： 在 operator= 中处理 “自我赋值”

1. 可以通过 `if (this == &rhs)` 来判断是否为同一个对象来处理自我赋值。
	- 不具备 **异常安全性**
2. 可以通过安排语句执行的顺序来保证 **异常安全性**，这样效率稍低但是更加的行得通；

## 条款12： 复制对象时复制每一个成分

1. 如果我们使用自定义的 copy constructor 和 copy assignment，当我们增加新的成员变量时，也需要修改我们的 copying function
2. 当我们为一个 derived class 编写 copying function 时，必须同时复制它的 derived class 的成员
	- 保证复制所有的 local 成员变量
	- 调用所有的 base class 内的 copying 函数
3. 通过 copy assignment 调用 copy constructor，或者通过 copy constructor 调用 copy assignment 都是不合适的：assignment 是修改一个 **已经存在对象** 的属性，constructor 是 **生成一个全新的对象**。
	- 合适的方式是给定一个 init 方法，并在两个函数中都调用 init 方法
