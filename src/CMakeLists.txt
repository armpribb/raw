add_executable(raw "")

target_sources(raw
    PRIVATE
        main.cpp
        convert_impl.cpp
        format_impl.cpp
        input_adapter.cpp
        log.cpp
        output_adapter.cpp
        parse.cpp
)

if(WIN)
    target_compile_definitions(raw PRIVATE UNICODE)
    target_sources(raw PRIVATE clipboard_impl_win.cpp)
    target_link_libraries(raw PRIVATE User32)
else()
    target_include_directories(raw PRIVATE ${clip_SOURCE_DIR})
    target_sources(raw PRIVATE clipboard_impl_unix.cpp)
    target_link_libraries(raw PRIVATE clip)
endif()

target_link_libraries(raw PRIVATE cxxopts nowide)

custom_target_sanitize_options(raw)
custom_target_debug_options(raw)

add_library(raw_headers INTERFACE)
target_include_directories(raw_headers INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(test)

