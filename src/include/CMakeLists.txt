cmake_minimum_required(VERSION 3.22.1)
 
set(TARGET generalInclude)

add_library(${TARGET} INTERFACE)

target_include_directories(${TARGET} INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")