cmake_minimum_required(VERSION 3.22)
project(AlgoLab)

set(CMAKE_CXX_STANDARD 14)
set(PROJECT_SOURCES
        main.cpp
        )

add_executable(AlgoLab main.cpp Binary.h Binary.cpp Calculator.h Calculator.cpp Stack.h Stack.cpp)
