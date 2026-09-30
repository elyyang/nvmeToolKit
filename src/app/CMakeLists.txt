cmake_minimum_required(VERSION 3.22.1)
 
set(TARGET app)

add_library(${TARGET} STATIC)

target_sources(${TARGET} PRIVATE controllerHandle.cpp)
 
target_include_directories(${TARGET} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(app PUBLIC lib drv generalUtil)
