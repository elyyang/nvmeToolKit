cmake_minimum_required(VERSION 3.22.1)
 
set(TARGET mock)

add_library(${TARGET} STATIC)

target_sources(${TARGET} PRIVATE mock_example.cpp)
 
target_include_directories(${TARGET} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${TARGET} PUBLIC inc)