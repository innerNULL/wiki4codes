# file: CMakeLists.txt
# date: 2021-06-01

 
cmake_minimum_required(VERSION 3.14)
project(example)


set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS " -pthread -std=c++17 -funroll-loops -O3 -march=native")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")


# Download cmakeup as pkg management.
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/build/main.zip")
    message(STATUS "cmakeup has been downloaded.")
else()
    execute_process(
        COMMAND wget https://ghproxy.com/https://github.com/innerNULL/cmakeup/archive/refs/heads/main.zip
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)
    execute_process(
        COMMAND unzip main.zip WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)
endif()
set(CMKAEUP_ROOT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/build/cmakeup-main/cmakeup")
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMKAEUP_ROOT_PATH}/module")
include(cmakeup)
cmakeup_init("${CMAKE_CURRENT_SOURCE_DIR}/build/_cmakeup_hub" "https://ghproxy.com/https://github.com")
cmakeup_root_path_register(${CMKAEUP_ROOT_PATH})
include(vcpkg_helpers)

integrate_vcpkg(
    "https://ghproxy.com/https://github.com/microsoft/vcpkg/archive/refs/heads/master.zip"  
    "${CMAKE_CURRENT_SOURCE_DIR}/build"
)
message(STATUS "All vcpkg pkg are installed under ${CMAKEUP_VCPKG_ROOT}/packages")

execute_process(COMMAND bash -c "${CMAKEUP_VCPKG_BIN} install opencv4[qt]")
find_package(OpenCV CONFIG REQUIRED)
execute_process(COMMAND bash -c "${CMAKEUP_VCPKG_BIN} install qt5")
#find_package(qt5 CONFIG REQUIRED)
find_package(Qt5 COMPONENTS Core Gui Qml Quick REQUIRED)

# The following is done in `integrate_vcpkg`.
#include(${CMAKEUP_VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)


add_executable(example "example.cpp")
target_link_libraries(example PRIVATE opencv_ml opencv_dnn opencv_core opencv_flann)

add_executable(ocr "ocr.cpp")
#target_link_libraries(ocr PRIVATE opencv_ml opencv_dnn opencv_core opencv_flann opencv_imgcodecs)
target_link_libraries(ocr ${OpenCV_LIBS})
target_link_libraries(ocr Qt5::Core Qt5::Gui Qt5::Qml Qt5::Quick)
