cmake_minimum_required(VERSION 3.8)
project(csapp)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        CMU/p1_course_overview/memery_bug.cpp
        CMU/p7/memery_bug.c
        CMU/
        offer
        leetcode)

add_executable(csapp ${SOURCE_FILES})
add_executable(offer offer/ch05/exec39_1.cpp offer/Utilities/BinaryTree.cpp)
add_executable(main offer/ch04/main.cpp)
add_executable(leetcode leetcode/easy/_709.cpp)
