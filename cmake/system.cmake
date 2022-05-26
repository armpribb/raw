# system identification

set(LIN OFF)
set(MAC OFF)
set(WIN OFF)

if(CMAKE_SYSTEM_NAME MATCHES "Linux")
    set(LIN ON)
elseif(CMAKE_SYSTEM_NAME MATCHES "Darwin")
    set(MAC ON)
elseif(CMAKE_SYSTEM_NAME MATCHES "Windows")
    set(WIN ON)
endif()


# compiler identification

set(CLANG OFF)
set(GCC OFF)
set(MSVC OFF)

if(CMAKE_C_COMPILER_ID MATCHES "Clang")
    set(CLANG ON)
elseif(CMAKE_C_COMPILER_ID STREQUAL "AppleClang")
    set(CLANG ON)
elseif(CMAKE_C_COMPILER_ID STREQUAL "GCC")
    set(GCC ON)
elseif(CMAKE_C_COMPILER_ID STREQUAL "MSVC")
    set(MSVC ON)
endif()

