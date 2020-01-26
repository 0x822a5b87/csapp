# 让自己习惯C++

## 条款01：视C++为一个语言联邦

1. C++ 是一个多范式编程语言 (multiparadigm programming language)
	- 过程式编程(procedural)
	- 面向对象(object-oriented)
	- 函数式编程(functional)
	- 泛型编程(generic)
	- 模板元编程(metaprogramming)
2. C++ 是四个次语言组成的联邦政府，所以每个语言都有着自己的最佳实践。

## 条款02：尽量以 const，enum， inline 替换 #define

1. `#define` 的定义只是简单的符号替换，甚至不会进入符号表(symbol table)，会为我们的 DEBUG 带来更多的困难
2. 有两个特殊情况：
	- 常量指针通常需要两个 const 来表示 const pointer point to const；一般声明在头文件中，以便于被其他的文件 include
	- class 的专属常量：例如一个 static member，我们可能需要在 class 的 {} 内和 {} 外声明/定义两次

```cpp
// 类型定义可以放在头文件中
class GamePlayer
{
	static const int NumTurns = 5;			// 常量声明
};

// 通常C++需要我们对所使用的任何东西提供一个定义
// 定义可以放在实现文件中
// 注意，由于已经在声明中获得初值，所以在定义时我们无法再一次对 const 变量赋值
const int GamePlayer::NumTurns;
```

3. 应该使用 inline 函数来代替 macro

## 条款03：尽可能使用 const

1. const 可以出现在非常多的地方
	- 出现在星号左边表示指向常量对象
	- 出现在星号右边表示指针是常量
	- 出现在类的成员函数声明的最右边，表明 `this` 是一个 const 对象
2. 在 STL 中，迭代器是一个指针 `T*`，所以当我们声明一个 `const std::vector<int>::iterator` 时得到的是 `const T*`，要使用 const 迭代器直接使用 `std::vector<int>::const_iterator` 即可

### const 成员函数

1. const 对象只能调用 const 成员函数
2. const 有两个不同的解释：(physical constness) 和 (logical constness)，C++ 是前一种。
	- physical constness 表示 const 成员函数不能修改对象内的任何非 non-static 成员变量
	- logical constness 表示 const 成员函数可以修改它所处对象内部的部分bits，但是只有在客户端侦测不出的情况才可以如此

### 在 const 和 non-const 成员函数中避免重复

>假设我们有一个成员函数，功能相当复杂。并且我们需要提供 const 成员函数和非 const 成员函数两个版本

1. 我们应该实现一个 const 成员函数，并且在非 const 成员函数中调用它的 const 版本。在内部我们可以通过 **const_cast** 和 **static_cast**。
	- 必须通过 **static_cast<const &Obj>** 将非 const 对象转换为 const 对象，否则在调用方法的时候会进入死循环递归
2. 不能通过在非 const 成员函数中调用，const 成员函数来实现相同的功能。

## 条款04：确定对象被使用之前已经被初始化

1. 对象的初始化动作何时发生十分复杂，我们最佳的处理方法就是：永远在使用对象之前将其初始化。对于无任何成员的内置类型，我们必须手动完成。而对于其他的类型，则需要依赖于构造函数
2. C++ 的构造函数提供了所谓的 **成员初值列表**，我们应当通过成员初值列表来初始化，它在构造器的函数体之前执行
3. 编译器会为用户自定义类型的成员变量自动调用默认构造函数（如果我们没有通过成员初值初始化该对象的话），而内置类型没有初值则不会初始化
4. **C++ 对于成员变量的初始顺序是 `声明顺序` 而不是成员初值的顺序**
5. 对于不同的 **编译单元** 中的 non-local static 对象，他们的初始化顺序非常的难以确定，所以我们可以通过将 non-local static 对象放到一个函数中，并在函数内部声明 static 对象并在函数结束时返回这个 static 对象。这样，我们十分简单的 non-local static 对象转换为 local static 对象避免这个问题
	- 编译单元（translation unit）是指产出单一目标文件的那些源码
6. <5> 中提到的这种通过 reference-returning 函数防止初始化顺序问题的会面临另外一个问题：static 对象在多线程下不安全，我们可以通过在程序的单线程启动阶段，手动的调用所有的 reference-returning 函数来避免

```cpp
// 文件 1
class FileSystem
{
	// ...
}
// 从 extern FileSystem fs 修改到 函数
FileSystem& tfs()
{
	static FileSystem fs;
	return fs;
}

// 文件2
class Dir
{
public:
	// ...
	Dir::Dir();
}

Dir::Dir()
{
	std::size_t disks = tfs().numDisks();
}

Dir& tempDir()
{
	// 使用 local static 对象代替 non-local static 对象
	// 否则，因为 td 和 fs 都是 non-local static 对象，那么当我们调用本函数
	// 时，Dir 的默认构造函数被调用，而它依赖于 fs 已经正常的初始化
	static Dir td;
	return td;
}
```


[non-local static](http://blog.csdn.net/chgaowei/article/details/6001433)
