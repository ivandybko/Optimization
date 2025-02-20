cmake_minimum_required(VERSION 3.30)
project(Lab_1__One_dimensional_optimization_)

set(CMAKE_CXX_STANDARD 20)

add_executable(Lab_1__One_dimensional_optimization_ main.cpp
        dichotomy_method.h
        golden_section_search.h)
