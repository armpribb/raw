# Sanitizer Build
if(MSVC)
    set(CMAKE_CXX_FLAGS_SANITIZE "/Zi /O1 /DEBUG" CACHE STRING "Flags used by the CXX compiler during SANITIZE builds." FORCE)
    set(CMAKE_EXE_LINKER_FLAGS_SANITIZE "/debug /INCREMENTAL:NO" CACHE STRING "Flags used by the linker during SANITIZE builds." FORCE)
else()
    set(CMAKE_CXX_FLAGS_SANITIZE "-g -O1" CACHE STRING "Flags used by the CXX compiler during Sanitizer builds." FORCE)
endif()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel Sanitize" FORCE)
endif()
