add_library(mock_include INTERFACE)
target_include_directories(mock_include INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_library(mock_convert STATIC mock_convert.cpp)
target_link_libraries(mock_convert PUBLIC raw_include)

add_library(mock_format STATIC mock_format.cpp)
target_link_libraries(mock_format PUBLIC raw_include)

add_library(mock_input STATIC mock_input.cpp)
target_link_libraries(mock_input PUBLIC raw_include)

add_library(mock_output STATIC mock_output.cpp)
target_link_libraries(mock_output PUBLIC raw_include)

