# file: CMakeLists.txt
# date: 2022-06-05

 
cmake_minimum_required(VERSION 3.14)
project(boostorg-beast-examples)

include(FetchContent)
include(ExternalProject)

set(CMAKE_BUILD_TYPE "Debug")
#set(CMAKE_CXX_FLAGS " -pthread -std=c++11 -funroll-loops -O3 -march=native")
set(CMAKE_CXX_FLAGS " -pthread -std=c++11 -funroll-loops -O3")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

set(FETCHCONTENT_QUIET FALSE)
#set(GIT_HOST "ghproxy.com/https://github.com")
set(GIT_HOST "github.com")

set(VCPKG_ROOT ${FETCHCONTENT_BASE_DIR}/vcpkg-src)
set(_VCPKG_BIN ${VCPKG_ROOT}/vcpkg)
set(_VCPKG_CMAKE 
  ${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)
set(CMAKE_TOOLCHAIN_FILE ${_VCPKG_CMAKE})

if (EXISTS ${_VCPKG_BIN})
  message(
    STATUS 
    "vcpkg already located at ${_VCPKG_BIN}")
  set(_VCPKG_EXISTS TRUE)
else()
  message(STATUS "downloading vcpkg first")
  FetchContent_Declare(
    vcpkg
    GIT_REPOSITORY https://${GIT_HOST}/microsoft/vcpkg.git  
    GIT_TAG 2022.02.02
    GIT_PROGRESS TRUE 
    DOWNLOAD_NO_PROGRESS FALSE
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
find_package(absl CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(Boost REQUIRED)
find_package(OpenSSL REQUIRED)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")


add_executable(
  ws_example "${CMAKE_CURRENT_SOURCE_DIR}/ws_example.cpp")
target_link_libraries(
  ws_example  
  PRIVATE absl::strings 
  PRIVATE nlohmann_json nlohmann_json::nlohmann_json 
  PRIVATE spdlog::spdlog spdlog::spdlog_header_only 
  PRIVATE Boost::boost 
  PRIVATE OpenSSL::SSL OpenSSL::Crypto)


add_executable(
  wss_binance_example 
  "${CMAKE_CURRENT_SOURCE_DIR}/wss_binance_example.cpp")
target_link_libraries(
  wss_binance_example   
  PRIVATE absl::strings 
  PRIVATE nlohmann_json nlohmann_json::nlohmann_json 
  PRIVATE spdlog::spdlog spdlog::spdlog_header_only 
  PRIVATE Boost::boost 
  PRIVATE OpenSSL::SSL OpenSSL::Crypto)
