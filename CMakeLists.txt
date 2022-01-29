cmake_minimum_required(VERSION 3.19)

project(raw LANGUAGES CXX VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_executable(raw "")

add_subdirectory(3rdparty)
add_subdirectory(src)
