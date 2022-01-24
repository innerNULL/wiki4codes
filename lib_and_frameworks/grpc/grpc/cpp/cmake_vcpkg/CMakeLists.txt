cmake_minimum_required(VERSION 3.14)
project(example)
include(ExternalProject)
include(FetchContent)


set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS 
  "-pthread -std=c++14 -funroll-loops -O3 -march=native")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

find_program(MAKE_EXE NAMES gmake nmake make)
set(GIT_HOST "ghproxy.com/https://github.com")

set(_PROTO_DIR ${CMAKE_SOURCE_DIR}/protos)
set(_PROTO_GEN_DIR ${CMAKE_SOURCE_DIR}/_pb_gen)
file(GLOB _PROTOS ${_PROTO_DIR}/*.proto)

set(FETCHCONTENT_QUIET FALSE)

set(VCPKG_FEATURE_FLAGS "versions")
set(VCPKG_ROOT ${FETCHCONTENT_BASE_DIR}/vcpkg-src)
set(_VCPKG_BIN ${VCPKG_ROOT}/vcpkg)
set(_VCPKG_CMAKE 
  ${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)
set(CMAKE_TOOLCHAIN_FILE ${_VCPKG_CMAKE})


if (EXISTS ${_VCPKG_BIN})
  message(
    STATUS 
    "vcpkg already located at:\n\t ${_VCPKG_BIN}")
  set(_VCPKG_EXISTS TRUE)
else()
  FetchContent_Declare(
    vcpkg
    GIT_REPOSITORY https://${GIT_HOST}/microsoft/vcpkg.git  
    GIT_TAG 2022.02.02
    GIT_PROGRESS TRUE 
    DOWNLOAD_NO_PROGRESS FALSE
    # <contentOptions>
    PATCH_COMMAND 
        cd <SOURCE_DIR> &&  
        bash <SOURCE_DIR>/bootstrap-vcpkg.sh)
  FetchContent_MakeAvailable(vcpkg)
endif()

include(${_VCPKG_CMAKE})
execute_process(
  COMMAND 
      ${_VCPKG_BIN} integrate install 
        --x-manifest-root=${CMAKE_SOURCE_DIR})

find_package(ZLIB REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)
find_package(protobuf CONFIG REQUIRED)

find_program(_PROTOC_BIN protoc)
find_program(_GRPC_CPP_PLUGIN grpc_cpp_plugin)

execute_process(
  COMMAND bash -c 
      "rm -rf ${_PROTO_GEN_DIR} && mkdir -p ${_PROTO_GEN_DIR}")
execute_process(
  COMMAND 
      ${_PROTOC_BIN} -I=${_PROTO_DIR} 
      --cpp_out=${_PROTO_GEN_DIR} 
      --grpc_out=${_PROTO_GEN_DIR} 
      --plugin=protoc-gen-grpc=${_GRPC_CPP_PLUGIN} 
      ${_PROTOS})
include_directories(${_PROTO_GEN_DIR})
file(GLOB _PROTO_GEN_SRC ${_PROTO_GEN_DIR}/*.cc)
set_source_files_properties(
  ${_PROTO_GEN_SRC} PROPERTIES GENERATED TRUE)


add_executable(
  helloworld_server 
  "./helloworld_server.cpp" ${_PROTO_GEN_SRC})
target_link_libraries(
  helloworld_server PRIVATE 
  ZLIB::ZLIB fmt::fmt 
  gRPC::grpc++ gRPC::grpc++_reflection 
  protobuf::libprotobuf)

add_executable(
  helloworld_client 
  "./helloworld_client.cpp" ${_PROTO_GEN_SRC})
target_link_libraries(
  helloworld_client PRIVATE 
  gRPC::grpc++ gRPC::grpc++_reflection) 



