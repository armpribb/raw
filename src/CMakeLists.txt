target_sources(raw
    PRIVATE
        main.cpp
        convert.cpp
        format.cpp
        input_adapter.cpp
        output_adapter.cpp
        parse.cpp
        print.cpp
)

if(WIN32)
    target_compile_definitions(raw PRIVATE UNICODE)
    target_sources(raw PRIVATE clipboard_impl_win.cpp)
    target_link_libraries(raw PRIVATE User32)
else()
    target_include_directories(raw PRIVATE ${clip_SOURCE_DIR})
    target_sources(raw PRIVATE clipboard_impl_unix.cpp)
    target_link_libraries(raw PRIVATE clip)
endif()

target_link_libraries(raw PRIVATE cxxopts nowide)
