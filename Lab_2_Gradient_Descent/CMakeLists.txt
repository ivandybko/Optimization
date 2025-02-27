cmake_minimum_required(VERSION 3.30)
project(Lab_2_Gradient_Descent)

set(CMAKE_CXX_STANDARD 20)

add_executable(Lab_2_Gradient_Descent main.cpp
        steepest_descent.h
        gradient_descent_step_split.h)
