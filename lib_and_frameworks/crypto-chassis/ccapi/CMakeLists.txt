# file: CMakeLists.txt
# date: 2022-09-30


cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
project(ccapi_example)


include(ExternalProject)


set(CMAKE_CXX_FLAGS
  "-fopenmp -pthread -std=c++14 -funroll-loops -O3 -march=native")


set(GITHUB_HOST 
  "ghproxy.com/https://github.com" 
  CACHE STRING INTERNAL)

ExternalProject_Add(
  ccapi
  PREFIX ${CMAKE_SOURCE_DIR}/build/_exts 
  GIT_REPOSITORY https://${GITHUB_HOST}/crypto-chassis/ccapi.git  
  GIT_TAG v5.31.3
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
  CONFIGURE_COMMAND ""
  GIT_PROGRESS TRUE
  DOWNLOAD_NO_PROGRESS FALSE
  LOG_DOWNLOAD ON 
  LOG_CONFIGURE ON 
  LOG_BUILD ON)
ExternalProject_Get_Property(ccapi install_dir)
message(STATUS "External projects directory: ${install_dir}")

find_package(OpenSSL REQUIRED)
include_directories(${install_dir}/src/ccapi/include)
include_directories(${install_dir}/src/ccapi/dependency/rapidjson/include)
include_directories(${install_dir}/src/ccapi/dependency/boost)
include_directories(${install_dir}/src/ccapi/dependency/websocketpp)


# Using cmakelist control internal marco variable, not recommended, 
# see subscriber_demo.cpp
add_compile_definitions(CCAPI_ENABLE_SERVICE_MARKET_DATA)
add_compile_definitions(CCAPI_ENABLE_EXCHANGE_COINBASE)
add_executable(subscriber_demo_v0 subscriber_demo_v0.cpp)
add_dependencies(subscriber_demo_v0 ccapi)
target_link_libraries(subscriber_demo_v0 OpenSSL::Crypto OpenSSL::SSL)

#add_executable(subscriber_demo subscriber_demo.cpp)
#add_dependencies(subscriber_demo ccapi)
#target_link_libraries(subscriber_demo OpenSSL::Crypto OpenSSL::SSL)

