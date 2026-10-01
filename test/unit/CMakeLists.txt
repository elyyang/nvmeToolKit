cmake_minimum_required(VERSION 3.22.1)
 
set(TARGET unit)

add_library(${TARGET} STATIC)

target_sources(${TARGET} PRIVATE udmaTest.cpp)
target_sources(${TARGET} PRIVATE writeDataTest.cpp)
 
target_include_directories(${TARGET} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${TARGET} PUBLIC drv)
target_link_libraries(${TARGET} PUBLIC prbsUtil)
target_link_libraries(${TARGET} PUBLIC generalUtil)