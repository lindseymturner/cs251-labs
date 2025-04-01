cmake_minimum_required(VERSION 3.1)
project(DoublePrecisionULong_CPP)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(-Wall -g -Wno-unused-function)  # add warnings, and -g makes stuff look nicer in debugger
include_directories(/home/courses/include ../HaverfordCS/include)


add_executable(DoublePrecisionULong_CPP
		main.cpp
		SafeInt.cpp
		safe_int_just_c.c
		DiS-p71and74.c
		countXs_just_c.c countXs_just_c.h all_names.cpp safe_int_just_c_tests.cpp)

