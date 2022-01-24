# file: CMakeLists.txt
# date: 2022-01-07

 
cmake_minimum_required(VERSION 3.14)
project(benchmark_example)

#include(ExternalProject)


include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

FetchContent_Declare(googlebenchmark
  GIT_REPOSITORY git@github.com:google/benchmark.git
  GIT_TAG v1.6.1 
  GIT_PROGRESS TRUE
)
set(BENCHMARK_ENABLE_GTEST_TESTS OFF)
FetchContent_MakeAvailable(googlebenchmark)


add_executable(example example.cpp)
target_link_libraries(example benchmark::benchmark)
