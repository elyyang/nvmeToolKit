cmake_minimum_required(VERSION 3.22.1)
 
set(TARGET lib)

add_library(${TARGET} STATIC)

target_sources(${TARGET} PRIVATE controllerMmio.cpp)
target_sources(${TARGET} PRIVATE pcieCfgSpace.cpp)
                                     
target_include_directories(${TARGET} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${TARGET} PUBLIC inc)
target_link_libraries(${TARGET} PUBLIC drv)