//
// Created by 杜航宇 on 2019-08-06.
//

#include "iostream"

using ulong = unsigned long;

void many_args(ulong, ulong, ulong, ulong, ulong, ulong, ulong, ulong)
{

}

void call_many_args()
{
    many_args(1ul, 2ul, 3ul, 4ul, 5ul, 6ul, 7ul, 8ul);
}

void q()
{
    int y = 1;
}

void p()
{
    q();
    int x = 0;
}
