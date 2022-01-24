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

execute_process(COMMAND bash -c "${CMAKEUP_VCPKG_BIN} install qt5")
find_package(Qt5 COMPONENTS Core Gui Qml Quick REQUIRED)


include_directories(${PROJECT_SOURCE_DIR}/incubator)


add_executable(hello_world "hello_world.cpp")
target_link_libraries(hello_world PRIVATE Qt5::Core Qt5::Gui Qt5::Qml Qt5::Quick)

add_executable(button "button.cpp")
set_target_properties(button PROPERTIES AUTOMOC TRUE)
target_link_libraries(button PRIVATE Qt5::Core Qt5::Gui Qt5::Qml Qt5::Quick)

add_executable(grid_layout "grid_layout.cpp")
target_link_libraries(grid_layout PRIVATE Qt5::Core Qt5::Gui Qt5::Qml Qt5::Quick)

add_executable(screen_shot "screen_shot.cpp")
target_link_libraries(screen_shot PRIVATE Qt5::Core Qt5::Gui Qt5::Qml Qt5::Quick)

add_executable(multi_frame "multi_frame.cpp")
target_link_libraries(multi_frame PRIVATE Qt5::Core Qt5::Gui Qt5::Qml Qt5::Quick)

add_executable(first_program "first_program.cpp")
target_link_libraries(first_program PRIVATE Qt5::Core Qt5::Gui Qt5::Qml Qt5::Quick)

add_executable(img_viewer "img_viewer.cpp")
set_target_properties(img_viewer PROPERTIES AUTOMOC TRUE)
target_link_libraries(img_viewer PRIVATE Qt5::Core Qt5::Gui Qt5::Qml Qt5::Quick)

add_executable(adv_screenshot "adv_screenshot.cpp")
set_target_properties(adv_screenshot PROPERTIES AUTOMOC TRUE)
target_link_libraries(adv_screenshot PRIVATE Qt5::Core Qt5::Gui Qt5::Qml Qt5::Quick)

