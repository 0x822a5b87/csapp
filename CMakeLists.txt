cmake_minimum_required(VERSION 3.8)
project(csapp)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        csapp/p1_course_overview/memery_bug.cpp
        csapp/p7/exec/7.1/memery_bug.c
        offer/ch02/exec13.cpp
        apue/part10/constructor.cpp
        csapp
        offer
        leetcode
        apue
        effective_cpp
        snippet
        挑战程序设计竞赛
        算法竞赛入门经典)

add_executable(csapp ${SOURCE_FILES})
add_executable(main offer/47.cpp)
add_executable(leetcode leetcode/easy/_709.cpp)
add_executable(server csapp/lab/proxylab-handout/csapp.c csapp/lab/proxylab-handout/proxy.c)
add_executable(algorithm leetcode/article/001/edit_distance.c)
add_executable(match 挑战程序设计竞赛/02/2.4/2.4.2.4.cpp)
