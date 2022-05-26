set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR amd64)


# clang target triple

set(TRIPLE x86_64-linux-gnu)


# compiler

set(CMAKE_C_COMPILER clang)
set(CMAKE_C_COMPILER_TARGET ${TRIPLE})
set(CMAKE_ASM_COMPILER ${CMAKE_C_COMPILER})
set(CMAKE_ASM_COMPILER_TARGET ${TRIPLE})
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_COMPILER_TARGET ${TRIPLE})


# compiler flags

set(CMAKE_C_FLAGS_INIT "-m64")
set(CMAKE_ASM_FLAGS_INIT "-m64")
set(CMAKE_CXX_FLAGS_INIT "-m64")

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
