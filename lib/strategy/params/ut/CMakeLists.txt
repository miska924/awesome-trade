add_executable(test_params test_params.cpp)

target_link_libraries(
    test_params
    PRIVATE
    params
    GTest::gtest_main
)

gtest_discover_tests(test_params)
