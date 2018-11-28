cmake_minimum_required(VERSION 3.12)
project(BTree)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(BTree
        BTree.h
        main.cpp
        node.h)
