cmake_minimum_required(VERSION 3.1)
project(UnsignedBigInt_CPP)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(-Wall -g -Wno-unused-function)  # add warnings, and -g makes stuff look nicer in debugger
include_directories(/home/courses/include ../HaverfordCS/include)


add_executable(UnsignedBigInt_CPP
		main.cpp
		SafeInt.cpp
		)

