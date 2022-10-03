add_executable(raw main.cpp)

add_library(raw_include INTERFACE)
target_include_directories(raw_include INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_library(raw_static STATIC)

target_sources(raw_static PUBLIC
    convert_impl.cpp
    format_impl.cpp
    input.cpp
    input_adapter.cpp
    log.cpp
    output.cpp
    output_adapter.cpp
    parse.cpp)

if(WIN)
    target_compile_definitions(raw_static PUBLIC UNICODE)
    target_sources(raw_static PUBLIC clipboard_impl_win.cpp)
    target_link_libraries(raw_static PUBLIC User32)
else()
    target_include_directories(raw_static PUBLIC ${clip_SOURCE_DIR})
    target_sources(raw_static PUBLIC clipboard_impl_unix.cpp)
    target_link_libraries(raw_static PUBLIC clip)
endif()

target_link_libraries(raw_static PUBLIC cxxopts nowide raw_include)

custom_target_sanitize_options(raw_static)
custom_target_debug_options(raw_static)

target_link_libraries(raw PRIVATE nowide raw_static)

custom_target_sanitize_options(raw)
custom_target_debug_options(raw)

add_subdirectory(test)

