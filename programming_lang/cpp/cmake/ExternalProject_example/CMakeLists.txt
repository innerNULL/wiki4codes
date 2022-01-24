cmake_minimum_required(VERSION 3.14)
project(example)
include(ExternalProject)
include(FetchContent)


set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS " -pthread -std=c++14 -funroll-loops -O3 -march=native")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

find_program(MAKE_EXE NAMES gmake nmake make)


ExternalProject_Add(
  abseil
  PREFIX _exts 
  GIT_REPOSITORY https://github.com.cnpmjs.org/abseil/abseil-cpp.git 
  GIT_TAG 20211102.0 
  CMAKE_ARGS 
      -DABSL_BUILD_TESTING=OFF 
      -DABSL_USE_GOOGLETEST_HEAD=OFF 
      -DCMAKE_CXX_STANDARD=14 
      -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR> 
  BUILD_COMMAND make -j12)
ExternalProject_Get_Property(abseil install_dir)
include_directories(${install_dir}/include)
link_directories(${install_dir}/lib)


ExternalProject_Add(
  spdlog
  PREFIX _exts 
  GIT_REPOSITORY https://github.com.cnpmjs.org/gabime/spdlog.git 
  GIT_TAG v1.9.2 
  CMAKE_ARGS 
      -DSPDLOG_BUILD_EXAMPLES=OFF 
      -DSPDLOG_BUILD_BENCH=OFF 
      -DSPDLOG_BUILD_TESTS=OFF 
      -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>)
ExternalProject_Get_Property(spdlog install_dir)
include_directories(${install_dir}/include)
link_directories(${install_dir}/lib)


ExternalProject_Add(
  json
  PREFIX _exts 
  GIT_REPOSITORY https://github.com.cnpmjs.org/nlohmann/json.git 
  GIT_TAG v3.10.5 
  CONFIGURE_COMMAND "" 
  BUILD_COMMAND "" 
  INSTALL_COMMAND "")
ExternalProject_Get_Property(json source_dir)
include_directories(${source_dir}/include)


FetchContent_Declare(
  pybind_pybind11
  GIT_REPOSITORY https://github.com.cnpmjs.org/pybind/pybind11.git 
  GIT_TAG v2.9.0 
  GIT_PROGRESS TRUE)
FetchContent_MakeAvailable(pybind_pybind11)

#ExternalProject_Add(
#        pybind11_external
#        GIT_REPOSITORY https://github.com/pybind/pybind11.git
#        GIT_TAG v2.2.1
#        CONFIGURE_COMMAND ""
#        BUILD_COMMAND ""
#        INSTALL_COMMAND ""
#)
#set(PYBIND11_CPP_STANDARD -std=c++14)
#ExternalProject_Get_Property(pybind11_external source_dir)
#include_directories(${source_dir}/include)
#add_subdirectory(${source_dir})           


add_executable(example "./example.cpp")
add_dependencies(example abseil)
add_dependencies(example spdlog)
add_dependencies(example json)
