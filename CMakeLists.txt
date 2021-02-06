cmake_minimum_required(VERSION 3.16.3)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

project(EasyHWND)

add_executable(${PROJECT_NAME} EasyHWND.h Example.cpp)
