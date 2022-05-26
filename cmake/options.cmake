include(CMakeDependentOption)

option(RAW_DEBUG_INFO "Build RAW with debug info" ON)

option(RAW_SANITIZE "Build RAW with Sanitizers" OFF)

cmake_dependent_option(RAW_SANITIZE_ADDRESS "Build RAW with Address Sanitizer" ON "RAW_SANITIZE" OFF)
cmake_dependent_option(RAW_SANITIZE_UNDEFINED "Build RAW with Undefined Behavior Sanitizer" ON "RAW_SANITIZE" OFF)

