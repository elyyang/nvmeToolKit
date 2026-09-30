cmake_minimum_required(VERSION 3.22.1)
 
set(TARGET menu)

add_library(${TARGET} STATIC)

target_sources(${TARGET} PRIVATE    menu.cpp)
 
target_include_directories(${TARGET} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(menu PUBLIC inc generalUtil)