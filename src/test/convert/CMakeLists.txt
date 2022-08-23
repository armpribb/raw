add_executable(convert_test "")

target_sources(convert_test PRIVATE
    test_convert.cpp
    ../../convert_impl.cpp)

target_link_libraries(convert_test PRIVATE
    gtest_main
    mock_format
    mock_include
    mock_input
    mock_output)

custom_target_sanitize_options(convert_test)
custom_target_debug_options(convert_test)

add_test(NAME convert-test COMMAND convert_test)

