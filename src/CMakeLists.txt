target_sources(raw
    PRIVATE
        main.cpp
        convert.cpp
        format.cpp
        input_adapter.cpp
        output_adapter.cpp
        parse.cpp
)

if(WIN32)
    target_compile_definitions(raw PRIVATE UNICODE)
    target_sources(raw PRIVATE clipboard_impl_win.cpp)
else()
    target_sources(raw PRIVATE clipboard_impl_unix.cpp)
endif()

target_link_libraries(raw PRIVATE cxxopts nowide)

if(WIN32)
    target_link_libraries(raw PRIVATE User32)
else()
endif()
