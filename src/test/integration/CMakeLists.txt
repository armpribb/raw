add_executable(integration_test "")

target_sources(integration_test PRIVATE test_integration.cpp)

target_link_libraries(integration_test PRIVATE
    gtest_main
    raw_static)

custom_target_sanitize_options(integration_test)
custom_target_debug_options(integration_test)

add_test(NAME integration-test COMMAND integration_test)

