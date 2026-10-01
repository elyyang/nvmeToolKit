cmake_minimum_required(VERSION 3.22.1)
 
set(TARGET generalUtil)

add_library(${TARGET} STATIC)

target_sources(${TARGET} PRIVATE displayData.c)
target_sources(${TARGET} PRIVATE generalLib.cpp)
target_sources(${TARGET} PRIVATE writeData.c)
 
target_include_directories(${TARGET} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${TARGET} PUBLIC include)