cmake_minimum_required(VERSION 3.20)

project(raw LANGUAGES C CXX VERSION 1.0)

include(cmake/system.cmake)
include(cmake/sanitize.cmake)
include(cmake/options.cmake)
include(cmake/utils.cmake)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

include(CTest)
configure_file(CTestCustom.cmake.in CTestCustom.cmake)

add_subdirectory(3rdparty EXCLUDE_FROM_ALL)
add_subdirectory(src)

