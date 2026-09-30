cmake_minimum_required(VERSION 3.22.1)
 
add_library(inc INTERFACE)
target_include_directories(inc INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")