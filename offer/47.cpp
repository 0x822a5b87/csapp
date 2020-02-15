#include <assert.h>

int Add(int num1, int num2)
{
    int sum, carry;

    // 这里用递归的思路来理解比较合理
    // num1 ^ num2        得到了所有 bit 不同的位相加之和
    // (num1 & num2) << 1 得到了所有 bit 相同的位相加之和
    // 这个时候只需要将这两个数字相加起来即可，而根据递归的思想，
    // 这个就是递归的去执行上面这一步
    // 知道没有进位即可
    do
    {

        // 不进位相加
        sum   = num1 ^ num2;
        // 只计算进位相加
        carry = ((num1 & num2) << 1);

        num1 = sum;
        num2 = carry;
    } while (carry != 0);

    return num1;
}

int main(int argc, char **argv)
{
    assert((16 + 5) == Add(16, 5));
    assert((105 + 102) == Add(105, 102));
}