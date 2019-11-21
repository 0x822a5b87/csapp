# link

1. 链接后的文件可以被 `加载` 到内存并执行。
2. 链接可以执行于 `编译时(compile time)`，也可以执行于 `加载时（load time）`，甚至是 `运行时（runtime time）`
3. `编译时（compile time)` 就是源代码被翻译成机器码
4. `加载时（load time）` 就是程序被加载器加载到内存并执行时
5. `运行时（runtime time)` 就是由应用程序来执行

## linker

1. 链接器（linker）的存在，使得我们在改变模块中的一个时，只需要重新编译它，**并重新链接应用**， 而不必重新编译其他文件。

## 7.1 compiler driver

1. compiler driver 会调用我们的预处理器、编译器、汇编器和链接器中的某一个；
2. 当我们执行 `g++ -Og -o prog main.cpp sum.cpp` 时，整个过程是这样的
    2.1 驱动程序通过预编译器生成 main.i
    2.2 驱动程序通过编译器生成 main.s
    2.3 驱动程序通过汇编器生成 main.o
    2.4 sum.cpp 也通过上面的步骤生成了 sum.o
    2.5 随后通过 linker（链接器程序 ld），将 main.o 和 sum.o 以及一些必要的系统目标文件组合起来，创建一个 `可执行文件（executable object file）`。
    
    
## 7.2 static linker

**为了构造可执行文件，链接器必须完成两个主要任务**

1. `符号解析（symbol resolution）`：目标文件定义和引用符号，**每个符号对应于一个函数、全局变量或者静态变量**，符号解析的目的是将每个 `符号引用` 和 `符号定义` 关联起来。
2. `重定位（relocation）`：编译器和汇编器生成从地址 0 开始的代码和 section。链接器通过把每个 `符号定义` 与一个 `内存位置` 关联起来，从而重定位这些 section，然后修改所有对这些符号的引用，使得它们指向这个内存的位置。
3. 目标文件是纯粹字节块的集合。这些块中，有些包含程序代码，有些包含程序数据，而其他的则包含引导链接器和加载器的数据结构。

## 7.3 目标文件

1. 可重定位目标文件
2. 可执行目标文件
3. 共享目标文件

## 7.5 符号和符号表

1. 每个可重定位的目标模块 m 都有一个符号表，包含了 m 定义和引用的符号信息
    1.1 全局符号：由 m 定义并能被其他模块引用的符号
    1.2 外部符号：由其他模块定义并被 m 引用的
    1.3 局部符号：只被模块 m 定义和引用的，对应于带上 static 的函数和全局变量。在 m 中任意位置可见，但不能被其他模块引用
2. 本地链接器符号和局部变量不一样， `.symtab` 中的符号表不包括任何对应于本地费静态程序变量的任何符号，这些符号在运行时在栈中被管理

### 符号表数据结构

```c++
// csapp 469
typedef struct {
    int name;
    char type:4,
         binding:4;
    char reserved;
    short section;
    long value;
    long size;
} Elf64_Symbol;
```

### readelf

对于通过 `g++ -c main.cpp -o main.o` 生成的目标代码，我们可以通过 `readelf -a main.o` 来读取（必须是 linux 下的 elf 文件）。也可以通过 `readelf -s main.o` 来读取 symbol 文件。

1. Ndx == 1 表示 `.text`， Ndx == 3 表示 `.data`
2. array 表示的是一个位于 `.data` 节的偏移量为 0 的 8 字节全局对象；
3. main 表示的是一个为 `.text` 节的偏移量为 0 的 31 字节的全局函数；

```c++
   Num:    Value          Size Type    Bind   Vis      Ndx Name
    12: 0000000000000000     8 OBJECT  GLOBAL DEFAULT    3 array
    13: 0000000000000000    31 FUNC    GLOBAL DEFAULT    1 main
    14: 0000000000000000     0 NOTYPE  GLOBAL DEFAULT  UND _Z3sumPii
```

### exec 6.7

```c++
// swap.cpp
extern int buf[];

int *bufp0 = &buf[0];
int *bufp1;

void swap()
{
    // do something
}
```

```c++
void swap();

int buf[2] = {1, 2};

int main()
{
    swap();
    return 0;
}
```

1. buf 是一个生成在 `main.o` 的 `.data` 的外部全局对象
2. bufp0 是一个生成在 `swap.o` 的 `.data` 的全局对象
3. bufp1 是一个生成在 `swap.o` 的 `.bss` 的全局对象
4. swap 是一个生成在 `swap.o` 的 `.text` 的全局函数

### 目标文件

1. .text 已编译程序的机器代码
2. .data `已初始化的全局和静态 C 变量`，局部变量在运行时被保存到栈中
3. .rodata 只读数据
4. .bss 未初始化的全局和静态 C 变量，以及所有被初始化为 0 的全局或静态变量

## 7.6 符号解析

1. 链接器解析符号引用的方法是将每个引用与它输入的可重定位目标文件中的符号表中的一个确定的符号关联起来
2. 对于全局符号的引用：当编译器遇到一个不是在当前模块中定义的符号时，会假设该符号是在其他的某个模块中定义的，生成一个链接器符号表条目，并把它交给链接器处理。


```c++
int foo(void);

int main() {
        foo();
        return 0;
}
```

- 对于上面的代码，gcc 会编译错误。

#### 7.6.1 链接器如何解析多重定义的全局符号

```c
#include "stdio.h"

void f(void);

int x = 15213;

int main()
{
    f();
    printf("x = %d\n", x);
    return 0;
}
```

---

```c
int x;

void f()
{
    x = 15212;
}
```

>gcc bar3.c foo3.c
>不会抛出异常。
>gcc -fno-common foo3.c bar3.c
>gcc 会抛出一个链接异常

### 7.6.2 与静态库链接

实际上，所有的编译系统都是提供一种机制，它将所有的相关的目标模块打包成一个单独的文件，称之为 `静态库(static library)`，他可以用作链接器的输入。当链接器构造一个输出的可执行文件时，他只复制静态库里被应用程序引用的目标模块。


#### 静态库的作用

1. 让编译器识别对标准库函数的调用；
2. 将所有的标准库函数编译到一个目标文件中，例如 `libc.o`，那么我们在使用某个函数时，需要连接所有的数据；
3. 使用静态库，单独编译所有的函数 (得到 printf.o, sprintf.o 等目标文件)，并封装在某个 `.a` 文件中。在解析的时候将将所有用到的 `.o` 文件加入到最终的可执行文件中

#### 7.6.3 链接器如何使用静态库来解析引用

1. 链接器会在符号解析阶段， `从左至右` 扫描。并生成三个集合：
    1.1 E 所有的 `.o` 文件
    1.2 U 所有的未解析的符号，例如我们调用了 `printf()`，那么 printf 就是一个未解析的符号
    1.3 D 所有已经解析的符号
2. 随后我们开始扫描，假设我们扫描到了两个文件，第一个文件调用了 printf，第二个文件是包含了 printf 的目标文件的静态库
    2.1 我们首先将文件添加到 E 中，随后我们识别到调用了 printf，将 printf 增加到 U 中
    2.2 随后我们扫描静态库，发现静态库包含了 printf 的定义，将 printf.o 添加到 E 中，并将 printf 从 U 移动到 D
3. 上面带来了一个问题，就是静态库必须在目标文件的后面。否则我们先扫描静态库，没有发现有 U 需要变动，所以 printf.o 不会被加入到 `E` 中。最后编译目标文件时会导致 `U` 中会包含一个未定义的引用。

### 7.3

```bash
gcc -static p.o libx.a

gcc -static p.o libx.a liby.a

# 这里不要在后面增加 p.o。因为只有静态链接库会选择性的打包到 E 中
gcc -static p.o libx.a liby.a libx.a
```

## 7.7 重定位

重定位分为两步：

1. 重定位节和符号定义：将所有的节合并，例如 `a.o` 和 `b.o` 都包含了 `.data` 节，我们合并成一个新的 `.data` 节。同时所有的在 `.data` 节中的位置都改变了
2. 重定位节中的符号引用：由于两个 `.data` 节合并了，所以我们必须将之前指向 `old.data` 的位置的符号引用指向新的 `.data` 位置

### 7.7.1 重定位条目

```c
typedef struct
{
    long offset;
    long type:32,
         symbol: 32;
    long addend;
} Elf64_Rela;
```

An addend is simply something that should be added to the fixed up address to find the correct address. For example, if the relocation is for the symbol i because the original code is doing something like i[8] the addend will be set to 8. This means "find the address of i, and go 8 past it

### 7.7.2 重定位符号引用

```
foreach section s {
    foreach relocation entry s {
        // 需要被重定位的指针
        refptr = s + r.offset
        
        // 重定位相对引用
        if (r.type == R_X86_64PC32) {
            refaddr = ADDR(s) + r.offset
            *refptr = (unsigned) (ADDR(r.symbol) + r.addend - refaddr)
        }
        
        // 重定位绝对引用
        if (r.type == R_X87_64_32) {
            *refptr = (unsigned) (ADDR(r.symbol) + r.addend)
        }
    }
}
```

#### 重定位PC相对引用

1. 我们通过 `objdump -dx main.o` 编译 7.1 的目标代码得到以下汇编程序

```asm
0000000000000000 <_main>:
   0:   55                      push   %rbp
   1:   48 89 e5                mov    %rsp,%rbp
   4:   48 83 ec 10             sub    $0x10,%rsp
   8:   c7 45 fc 00 00 00 00    movl   $0x0,-0x4(%rbp)
   f:   48 8d 3d 00 00 00 00    lea    0x0(%rip),%rdi        # 16 <_main+0x16>
                        12: DISP32      _array
  16:   be 02 00 00 00          mov    $0x2,%esi
  1b:   e8 00 00 00 00          callq  20 <_main+0x20>
                        1c: BRANCH32    __Z3sumPii
  20:   89 45 f8                mov    %eax,-0x8(%rbp)
  23:   8b 45 f8                mov    -0x8(%rbp),%eax
  26:   48 83 c4 10             add    $0x10,%rsp
  2a:   5d                      pop    %rbp
  2b:   c3                      retq   

```

在这两行程序中

```asm
  1b:   e8 00 00 00 00          callq  20 <_main+0x20>
                        1c: BRANCH32    __Z3sumPii
```

1. 我们知道 callq 后面跟着的 20 和 <_main+0x20> 是调用完 callq 之后需要执行的指令地址的两种表示形式
2. callq 指令开始于偏移量 1b 的地方，包括 1 字节的操作码 e8，后面紧跟着的是对目标 sum 的 32 位 PC 相对引用的占位符。 **注意，这个时候我们的 call 指令调用的地址还是 00 00 00，因为目标文件是尚未链接的，我们还不知道我们将要调用的 sum 函数的实际地址**
3. 通过 `1c: BRANCH32    __Z3sumPii` 我们知道我们要调用的函数，这个时候我们要将 `sum` 函数的实际地址来替换 <2> 提到的 `00 00 00`
4. 我们的重定位条目属性为 offset = 1c, type = BRANCH32, symbol = sum, addend = -4
5. 段的地址为 ADDR(s) = ADDR(.text)
6. 符号的地址为 ADDR(r.symbol) = ADDR(sum)
7. 所以我们 call 指令的地址为 refaddr = ADDR(s) + 0x1c
8. 所以相对地址为 ADDR(sum) + r.addend - refaddr

### 7.10 动态链接共享库

1. 共享库是一个目标模块，在运行或者加载时可以加载到任意的内存地址，并和一个在内存中的程序链接起来。在 linux 中通常为 `.so`，在 windows 中通常为 `DLL`
2. 静态库针对每个可执行文件都必须有一份副本，而共享库可以所有进程共享






















