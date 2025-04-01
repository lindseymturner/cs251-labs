cmake_minimum_required(VERSION 3.1)
project(Lab1H_Fibonacci)

set(CMAKE_CXX_STANDARD 20)

# Add all relevant source files, including fibonacci.hera
add_executable(Lab1H_Fibonacci
        main.cpp
        fibonacci.hera
        )

include_directories(/home/courses/lib/HERA-C /home/courses/lib/HERA-libb ../HERA-C ../HERA-libb)

