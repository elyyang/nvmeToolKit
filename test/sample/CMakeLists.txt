cmake_minimum_required(VERSION 3.22.1)
 
set(TARGET sample)

add_library(${TARGET} STATIC)

target_sources(${TARGET} PRIVATE demo.cpp)
 
target_include_directories(${TARGET} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${TARGET} PUBLIC app)
target_link_libraries(${TARGET} PUBLIC menu)