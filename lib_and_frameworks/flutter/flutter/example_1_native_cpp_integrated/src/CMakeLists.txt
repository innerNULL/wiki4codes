# The Flutter tooling requires that developers have CMake 3.10 or later
# installed. You should not increase this version, as doing so will cause
# the plugin to fail to compile for some customers of the plugin.
cmake_minimum_required(VERSION 3.10)

project(example_1_native_cpp_integrated_library VERSION 0.0.1 LANGUAGES C)

add_library(example_1_native_cpp_integrated SHARED
  "example_1_native_cpp_integrated.c"
)

set_target_properties(example_1_native_cpp_integrated PROPERTIES
  PUBLIC_HEADER example_1_native_cpp_integrated.h
  OUTPUT_NAME "example_1_native_cpp_integrated"
)

target_compile_definitions(example_1_native_cpp_integrated PUBLIC DART_SHARED_LIB)
