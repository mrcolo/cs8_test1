cmake_minimum_required(VERSION 3.9)
project(calculator)

set(CMAKE_CXX_STANDARD 11)

add_executable(calculator
        Calculator.cpp
        Calculator.h
        main.cpp
        Queue.h
        Stack.h)
