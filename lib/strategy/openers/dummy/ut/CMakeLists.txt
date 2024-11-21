add_executable(test_dummy_opener test_opener.cpp)

target_link_libraries(
    test_dummy_opener
    PRIVATE
    dummy_opener
    params
    GTest::gtest_main
)

gtest_discover_tests(test_dummy_opener)
