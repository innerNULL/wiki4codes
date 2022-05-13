# file: CMakeLists.txt
# date: 2022-05-13

 
cmake_minimum_required(VERSION 3.14)
project(tgbot-cpp-demo)

include(FetchContent)
include(ExternalProject)

set(CMAKE_BUILD_TYPE "Debug")
#set(CMAKE_CXX_FLAGS " -pthread -std=c++11 -funroll-loops -O3 -march=native")
set(CMAKE_CXX_FLAGS " -pthread -std=c++11 -funroll-loops -O3")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

set(FETCHCONTENT_QUIET FALSE)
set(GIT_HOST "ghproxy.com/https://github.com")

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

find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)
find_package(CURL)
include_directories(
  /usr/local/include 
  ${OPENSSL_INCLUDE_DIR} ${Boost_INCLUDE_DIR})
if (CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIRS})
    add_definitions(-DHAVE_CURL)
endif()


add_executable(main main.cpp)
target_link_libraries(main 
  ${VCPKG_ROOT}/packages/tgbot-cpp_arm64-osx/lib/libTgBot.a 
  ${CMAKE_THREAD_LIBS_INIT} 
  ${OPENSSL_LIBRARIES} 
  ${Boost_LIBRARIES} 
  ${CURL_LIBRARIES})
