target_sources(raw
    PRIVATE
        main.cpp
        converter.cpp
        formatter.cpp
        input_adapter.cpp
        output_adapter.cpp
)

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_definitions(raw PRIVATE UNICODE)
else()
endif()
    
if(WIN32)
    target_sources(raw PRIVATE clipboard_impl_win.cpp)
else()
endif()

target_link_libraries(raw PRIVATE nowide User32)
