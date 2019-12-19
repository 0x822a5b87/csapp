cmake_minimum_required(VERSION 3.8)
project(csapp)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        CMU/p1_course_overview/memery_bug.cpp
        CMU/p7/exec/7.1/memery_bug.c
        CMU
        offer
        leetcode)

add_executable(csapp ${SOURCE_FILES})
add_executable(main offer/ch04/main.cpp)
add_executable(leetcode leetcode/easy/_709.cpp)
add_executable(server CMU/p12/echoserver-pre.c CMU/p12/echo-cnt.c CMU/p12/sbuf.c CMU/csapp.c)
#add_executable(offer CMU/lab/malloclab-handout/mdriver.c CMU/lab/malloclab-handout/fsecs.h CMU/lab/malloclab-handout/fsecs.c CMU/lab/malloclab-handout/fcyc.h CMU/lab/malloclab-handout/clock.h CMU/lab/malloclab-handout/memlib.h CMU/lab/malloclab-handout/config.h CMU/lab/malloclab-handout/mm.h CMU/lab/malloclab-handout/memlib.c CMU/lab/malloclab-handout/memlib.h CMU/lab/malloclab-handout/mm.c CMU/lab/malloclab-handout/mm.h CMU/lab/malloclab-handout/memlib.h CMU/lab/malloclab-handout/config.h CMU/lab/malloclab-handout/fcyc.c CMU/lab/malloclab-handout/ftimer.c CMU/lab/malloclab-handout/ftimer.h CMU/lab/malloclab-handout/config.h CMU/lab/malloclab-handout/clock.c CMU/lab/malloclab-handout/clock.h)
