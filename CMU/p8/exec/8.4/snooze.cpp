//
// Created by 杜航宇 on 2019-11-28.
//

#include <zconf.h>
#include "iostream"

unsigned int snooze(unsigned int secs)
{
    unsigned int rc = sleep(secs);
    printf("Slept for [%u] of [%u] secs.\n", secs - rc, secs);
    return rc;
}

