//
// Created by 杜航宇 on 2019-08-30.
//

#include "iostream"
#include <sys/time.h>

#define IDENT 1
#define OP *

typedef long data_t;

typedef struct
{
    long   len;
    data_t *data;
}            vec_rec, *vec_ptr;

long vec_length(vec_ptr);
vec_ptr new_vec(long);
int get_vec_element(vec_ptr, long, data_t *);

void combine1(vec_ptr v, data_t *dest)
{
    long i;
    *dest = IDENT;
    // 容器的长度不会变，所以我们可以在循环外求值
    for (i = 0; i < vec_length(v); ++i)
    {
        data_t val;
        get_vec_element(v, i, &val);
        *dest += val;
    }
}

void combine2(vec_ptr v, data_t *dest)
{
    *dest = IDENT;
    long len = vec_length(v);
    for (size_t i = 0; i < len; ++i)
    {
        data_t val;
        // 每次调用 get_vec_element 都会将向量索引与循环边界做比较
        get_vec_element(v, i, &val);
        *dest += val;
    }
}

data_t *get_vec_start(vec_ptr ptr)
{
    return ptr->data;
}

// combine3 不调用 get_vec_element，实际上性能优化很小
void combine3(vec_ptr v, data_t *dest)
{
    *dest = IDENT;
    long len = vec_length(v);
    data_t *beg = get_vec_start(v);
    for (size_t i = 0; i < len; ++i)
    {
        *dest = *dest OP beg[i];
    }
}

void combine3_o2(vec_ptr v, data_t *dest)
{
    *dest = IDENT;
    long len = vec_length(v);
    data_t *beg = get_vec_start(v);
    data_t tmp = *dest;
    for (size_t i = 0; i < len; ++i)
    {
        tmp = tmp OP beg[i];
        *dest = tmp;
    }
}

// 在 combine4 中每只访问一次内存，而 combine3 每次循环需要访问三次内存
void combine4(vec_ptr ptr, data_t *dest)
{
    long len = vec_length(ptr);
    data_t *data = get_vec_start(ptr);
    data_t tmp = IDENT;
    for (int i = 0; i < len; ++i)
    {
        tmp = tmp OP data[i];
    }
    *dest = tmp;
}

vec_ptr new_vec(long len)
{
    // 分配 header
    vec_ptr result = (vec_ptr) malloc(sizeof(vec_rec));
    data_t  *data  = nullptr;
    if (!result)
    {
        return nullptr;
    }
    // 分配 data
    if (len > 0)
    {
        data = (data_t *) calloc(len, sizeof(data_t));
        if (!data)
        {
            free((void *) result);
            return nullptr;
        }
        result->len  = len;
        result->data = data;
    }

    return result;
}

int get_vec_element(vec_ptr v, long index, data_t *dest)
{
    // 之所以取消掉这个函数之后优化不大，主要有两个原因
    // 1. 这个函数不在程序的关键路径上，所以它对程序的影响比较小
    // 2. 对于这个函数来讲，这些检测总是确定索引在界内，所以 CPU 的分支预测正确的概率非常大。也就是分支预测错误的惩罚非常小
    if (index < 0 || index >= v->len)
    {
        return 0;
    }

    *dest = v->data[index];
    return 1;
}

long vec_length(vec_ptr v)
{
    return v->len;
}

int main()
{
    timeval start{}, end{};
    gettimeofday(&start, nullptr);
    std::cout << start.tv_sec << std::endl;
    vec_ptr ptr = new_vec(100000000);
    data_t d;
    combine1(ptr, &d);
    gettimeofday(&end, nullptr);
    std::cout << (end.tv_sec - start.tv_sec) << std::endl;
}
