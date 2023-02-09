# file: CMakeLists.txt
# date: 2023-02-10


cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(CPM_demo)


# get CPM
if(NOT EXISTS "${CMAKE_BINARY_DIR}/CPM.cmake")
  file(
    DOWNLOAD
    "https://raw.githubusercontent.com/cpm-cmake/CPM.cmake/master/cmake/CPM.cmake" 
    "${CMAKE_BINARY_DIR}/CPM.cmake"
  )
endif()


# add dependencies
include(${CMAKE_BINARY_DIR}/CPM.cmake)
CPMAddPackage("gh:fmtlib/fmt#7.1.3")
CPMAddPackage("gh:nlohmann/json@3.10.5")
CPMAddPackage("gh:catchorg/Catch2@3.2.1")

CPMAddPackage(
  NAME Boost
  VERSION 1.81.0
  GITHUB_REPOSITORY "boostorg/boost"
  GIT_TAG "boost-1.81.0"
)


# link dependencies
add_executable(main main.cpp)
target_link_libraries(
  main 
  fmt::fmt nlohmann_json::nlohmann_json Catch2::Catch2WithMain
)
