cmake_minimum_required(VERSION 3.8)
project(csapp)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES CMU/p1_course_overview/memery_bug.cpp
                 CMU/)

add_executable(csapp ${SOURCE_FILES})

