include(CMakeDependentOption)

option(RAW_DEBUG_INFO "Build RAW with debug info" ON)

cmake_dependent_option(RAW_RECORD_COMPILE_SWITCHES "Record compile switches" ON "NOT MSVC" OFF)

set(RAW_SANITIZER_TYPE "ASAN" CACHE STRING "Specifiy Sanitizer to use: ASAN, UBSAN, LSAN, MSAN, TSAN")
