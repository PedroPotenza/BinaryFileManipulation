cmake_minimum_required(VERSION 3.20)
project(BinaryFileManipulation)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(BinaryFileManipulation
        code/Compress.c
        code/Insert.c
        code/Remove.c
        code/tempCodeRunnerFile.c
        code/Util.c
        BinaryManipulation.c
        header.h
        insere.cpp)
