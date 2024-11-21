add_executable(test_cross_closer test_closer.cpp)

target_link_libraries(
    test_cross_closer
    PRIVATE
    cross_closer
    dummy_feature
    params
    GTest::gtest_main
)

gtest_discover_tests(test_cross_closer)
