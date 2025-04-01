cmake_minimum_required(VERSION 3.1)
project(Arithmetic)

if (${CMAKE_BUILD_TYPE} STREQUAL "Release")
	add_compile_options(-O3 -DCHECK_LOGIC=0 -DNDEBUG)
else()  # hopefully "Debug"
 	add_compile_options(-Wall -Wextra -g -Wno-unused-function)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 11)

add_executable(Arithmetic
		factorial.cpp
		countXs.cpp
		main.cpp
		hc_streams.cpp
		countXs.h power.cpp power.h)

include_directories(/home/courses/include ../HaverfordCS/include)
