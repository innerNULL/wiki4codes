# file: CMakeLists.txt
# date: 2022-01-07

 
cmake_minimum_required(VERSION 3.14)
project(benchmark_example)

#include(ExternalProject)


include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

FetchContent_Declare(
  tdlib_td
  GIT_REPOSITORY https://github.com/tdlib/td.git 
  GIT_TAG v1.8.0 
  GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(tdlib_td)


add_executable(examples examples.cpp)
target_link_libraries(examples PRIVATE Td::TdStatic)
set_property(TARGET examples PROPERTY CXX_STANDARD 14)
