cmake_minimum_required(VERSION 3.22)

project(raw VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_executable(raw "")
add_subdirectory(src)
add_subdirectory(nowide)
add_subdirectory(cxxopts)
