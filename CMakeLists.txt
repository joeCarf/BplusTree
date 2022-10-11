cmake_minimum_required(VERSION 3.23)
project(BplusTree)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(BplusTree
        BPlusTree.h
        main.cpp)
