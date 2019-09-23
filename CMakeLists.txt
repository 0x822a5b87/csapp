cmake_minimum_required(VERSION 3.8)
project(csapp)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        CMU/p1_course_overview/memery_bug.cpp
        CMU/p7/memery_bug.c
        CMU/
        offer)

add_executable(csapp ${SOURCE_FILES})
add_executable(exec07 offer/ch02/exec07.cpp)
add_executable(exec08 offer/ch02/exec08.cpp)
add_executable(exec11 offer/ch02/exec11.cpp)
