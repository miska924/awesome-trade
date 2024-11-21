add_executable(test_cross_opener test_opener.cpp)

target_link_libraries(
    test_cross_opener
    PRIVATE
    cross_opener
    dummy_feature
    params
    GTest::gtest_main
)

gtest_discover_tests(test_cross_opener)
