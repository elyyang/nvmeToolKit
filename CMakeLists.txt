cmake_minimum_required(VERSION 3.22.1)

set(CMAKE_C_COMPILER gcc CACHE FILEPATH "C compiler")
set(CMAKE_CXX_COMPILER g++ CACHE FILEPATH "C++ compiler")
#set(CMAKE_C_COMPILER clang CACHE FILEPATH "C compiler")
#set(CMAKE_CXX_COMPILER clang++ CACHE FILEPATH "C++ compiler")

project(default)

string(TIMESTAMP BUILD_DATE "%Y%m%d")
set(PROJECT_NAME "nvmeToolKit_${BUILD_DATE}")
set(PROJECT_LANGUAGES CXX C)
set(PROJECT_VERSION 1.0.0)

# Project information:
message(STATUS "Project name: ${PROJECT_NAME}")
message(STATUS "Project version ${PROJECT_VERSION}")
message(STATUS "Project language: ${PROJECT_LANGUAGES}")

# Compiler information:
if(CMAKE_CXX_COMPILER_LOADED)
    set(CMAKE_CXX_STANDARD 11)
    set(CMAKE_CXX_EXTENSIONS OFF)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)

    message(STATUS "C++ compiler: ${CMAKE_CXX_COMPILER}")
    message(STATUS "C++ compiler ID: ${CMAKE_CXX_COMPILER_ID}")
    message(STATUS "C++ compiler version: ${CMAKE_CXX_COMPILER_VERSION}")
    message(STATUS "C compiler: ${CMAKE_C_COMPILER}")
    message(STATUS "Cmake tool chain file: ${CMAKE_TOOLCHAIN_FILE}")
else()
    message(FATAL_ERROR "C++ compiler not found")
endif()

# OS information:
message(STATUS "System name: ${CMAKE_SYSTEM_NAME}")
message(STATUS "System processor: ${CMAKE_SYSTEM_PROCESSOR}")
message(STATUS "System version: ${CMAKE_SYSTEM_VERSION}")

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(util)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE sampleTest)
target_link_libraries(${PROJECT_NAME} PRIVATE unitTest)
target_link_libraries(${PROJECT_NAME} PRIVATE menuUtil)
