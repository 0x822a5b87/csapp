cmake_minimum_required(VERSION 3.8)
project(csapp)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        csapp/p1_course_overview/memery_bug.cpp
        csapp/p7/exec/7.1/memery_bug.c
        csapp
        offer
        leetcode
        apue)

add_executable(csapp ${SOURCE_FILES})
add_executable(main offer/ch04/main.cpp)
add_executable(leetcode leetcode/easy/_709.cpp)
add_executable(server csapp/lab/proxylab-handout/csapp.c csapp/lab/proxylab-handout/proxy.c)
