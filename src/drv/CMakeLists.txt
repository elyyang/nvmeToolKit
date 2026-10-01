cmake_minimum_required(VERSION 3.22.1)
 
set(TARGET drv)

add_library(${TARGET} STATIC)

target_sources(${TARGET} PRIVATE udma.cpp)
target_sources(${TARGET} PRIVATE uio.cpp)
 
target_include_directories(${TARGET} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${TARGET} PUBLIC inc)
target_link_libraries(${TARGET} PUBLIC generalUtil)