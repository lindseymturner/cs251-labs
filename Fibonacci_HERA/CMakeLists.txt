cmake_minimum_required(VERSION 3.1)
project(Algorithms_HERA)

set(CMAKE_CXX_STANDARD 20)

# Note that the .hera files get #include'd, so we don't need to list them below
add_executable(Fibonacci_HERA HERA_main)

include_directories(/home/courses/lib/HERA-C /home/courses/lib/HERA-lib
        ../HERA-C ../HERA-lib)

