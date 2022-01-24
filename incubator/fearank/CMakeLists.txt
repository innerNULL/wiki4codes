# file: CMakeLists.txt
# date: 2022-02-09

 
cmake_minimum_required(VERSION 3.14)
project(fearank)

include(ExternalProject)
include(FetchContent)

set(
  CMAKE_CXX_FLAGS 
  "-fopenmp -pthread -std=c++14 -funroll-loops -O3 -march=native")

find_program(MAKE_EXE NAMES gmake nmake make)

set(GIT_HOST ghproxy.com/https://github.com)


ExternalProject_Add(
  abseil
  PREFIX _exts 
  GIT_REPOSITORY https://${GIT_HOST}/abseil/abseil-cpp.git 
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
  duckdb
  PREFIX _exts 
  GIT_REPOSITORY https://${GIT_HOST}/duckdb/duckdb.git 
  GIT_TAG v0.3.2 
  CMAKE_ARGS
      -DBUILD_UNITTESTS=FALSE 
      -DBUILD_ARROW_ABI_TEST=FALSE 
      -DTEST_REMOTE_INSTALL=FALSE 
      -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR> 
  BUILD_COMMAND make -j12)
ExternalProject_Get_Property(duckdb install_dir)
include_directories(${install_dir}/include)
link_directories(${install_dir}/lib)


add_executable(fearank "./fearank.cpp")
add_dependencies(fearank abseil)
add_dependencies(fearank duckdb)
