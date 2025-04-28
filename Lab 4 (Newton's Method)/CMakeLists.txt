cmake_minimum_required(VERSION 3.30)
project(Lab_4__Newton_s_Method_)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Lab_4__Newton_s_Method_
    main.cpp
    newton_method.h
    newton_method_with_steepest_descent.h)
