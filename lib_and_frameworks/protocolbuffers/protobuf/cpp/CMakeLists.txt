# file: CMakeLists.txt
# date: 2022-02-10

 
cmake_minimum_required(VERSION 3.14)
project(pb_cpp_example)

include(FetchContent)
include(ExternalProject)

# No compiling optimization, very slow
#set(CMAKE_CXX_FLAGS "-fopenmp") 
# Compiling optimization params
set(CMAKE_CXX_FLAGS 
  "-fopenmp -pthread -std=c++14 -funroll-loops -O3 -march=native")


option(BENCHMARK "Benchmarking." ON)
option(PYBIND "Builds python binder." ON)


set(FETCHCONTENT_QUIET FALSE)
#set(DOWNLOAD_NO_PROGRESS FALSE)
set(GIT_HOST "ghproxy.com/https://github.com")
set(PROTO_DIR ${CMAKE_SOURCE_DIR}/proto)
file(GLOB PROTOS ${PROTO_DIR}/*.proto)

# NOTE:
# The reason not using `GIT_REPOSITORY` and `GIT_TAG` is, 
# it seems setting `GIT_SUBMODULES` to '' is not work, 
# `ExternalProject_Add` will still clone git submodules 
# before compiling.
# Following integration process is refered to 
# https://stackoverflow.com/questions/52149504/using-protobuf-in-cmake-as-externalproject
ExternalProject_Add(
  protobuf
  PREFIX _ext
  URL https://${GIT_HOST}/protocolbuffers/protobuf/releases/download/v3.19.4/protobuf-cpp-3.19.4.tar.gz
  GIT_PROGRESS TRUE 
  DOWNLOAD_NO_PROGRESS FALSE 
  #BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/protobuf
  CMAKE_CACHE_ARGS
    -DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE} 
    -Dprotobuf_BUILD_TESTS:BOOL=OFF 
    -Dprotobuf_BUILD_EXAMPLES:BOOL=OFF 
    -Dprotobuf_WITH_ZLIB:BOOL=OFF 
    -DCMAKE_CXX_COMPILER:STRING=${CMAKE_CXX_COMPILER} 
    -DCMAKE_INSTALL_PREFIX:STRING=<INSTALL_DIR> 
  SOURCE_SUBDIR cmake
  BUILD_ALWAYS 1
  STEP_TARGETS build 
  GIT_SUBMODULES "" 
  INSTALL_COMMAND "" 
  COMMAND 
      rm -rf ${CMAKE_SOURCE_DIR}/_pb_out 
        && mkdir -p ${CMAKE_SOURCE_DIR}/_pb_out 
  COMMAND 
      <INSTALL_DIR>/src/protobuf-build/protoc 
        -I=${CMAKE_SOURCE_DIR}/proto 
        --cpp_out=${CMAKE_SOURCE_DIR}/_pb_out 
        ${PROTOS})
ExternalProject_Get_Property(protobuf install_dir source_dir)
set(PROTOBUFC_BIN ${install_dir}/src/protobuf-build/protoc)
message(STATUS "The 'protoc' located at:\n\t${PROTOBUFC_BIN}")
include_directories(${source_dir}/src)
link_directories(${install_dir}/src/protobuf-build)


add_executable(server server.cpp)
add_dependencies(server protobuf)
