//
// Created by 杜航宇 on 2019-08-04.
//
// P147
// 对比流水线预测的性能
// 当直接通过 gcc 编译时生成的代码会包含条件跳转，这有可能破坏CPU流水线的状态
// 当通过 gcc -O1 编译时生成的代码会使用条件数据传送代替条件条状，这将不会破坏流水线状态。
// 缺点是必须在返回值之前计算所有的结果，所以对于条件跳转指令中的指令非常短时十分有效
// 简单来说就是，假设 if {} else {} 的 {} 中语句特别短时非常有效

#include "iostream"
#include "ctime"
#include "random"
using std::chrono::milliseconds;
using std::chrono::duration_cast;
using std::chrono::system_clock;

int abs_jump(int x, int y)
{
    return x > y ? (x - y) : (y - x);
}

//int abs_pred(int x, int y)
//{
//    int rval = y - x;
//    int eval = x - y;
//    int test = (x >= y);
//
//    if (test)
//    {
//        rval = eval;
//    }
//    return rval;
//}

int main()
{
    int cnt = INT_MAX;
    milliseconds now = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
    for (int i = 0; i < cnt; ++i)
    {
        abs_jump(1, 2);
    }
    milliseconds end = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
    std::cout << (end.count() - now.count()) << std::endl;
}
