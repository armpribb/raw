cmake_minimum_required(VERSION 3.20)

project(raw LANGUAGES C CXX VERSION 1.0)

include(cmake/system.cmake)
include(cmake/sanitize.cmake)
include(cmake/options.cmake)
include(cmake/utils.cmake)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

enable_testing()

add_subdirectory(3rdparty)
add_subdirectory(src)

