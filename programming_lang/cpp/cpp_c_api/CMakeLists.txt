# file: CMakeLists.txt
# date: 2024-01-07


cmake_minimum_required(VERSION 3.10)
project(demo_lib VERSION 0.0.1)


# Add the C++ source files
set(CPP_SOURCES
    calculator.cpp
    calculator_c_wrapper.cpp
)

# Add the header files
set(HEADERS
    calculator.hpp
    calculator_c_wrapper.h
)

# Create a shared library from the C++ source files
add_library(calculator_lib SHARED ${CPP_SOURCES})

# Create an executable for testing the library
add_executable(calculator_run calculator_run.c)

# Link the executable with the library
target_link_libraries(calculator_run calculator_lib)
