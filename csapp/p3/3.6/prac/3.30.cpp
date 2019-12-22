//
// Created by 杜航宇 on 2019-08-05.
//

#include "iostream"

/**
 * 1. (x + 1) > 8 会导致跳到 default，所以最大 case 为 7
 */

void switch2(int x)
{
    switch (x)
    {
        case 1:
            printf("%d", 1);
            break;
        case 3:
            printf("%d", 3);
            break;
        default:
            printf("%d", 4);
            break;
    }
}

