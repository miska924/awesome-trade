add_executable(test_strategy test_strategy.cpp)

target_link_libraries(
    test_strategy
    PRIVATE
    strategy
    params
    dummy_opener
    dummy_closer
    GTest::gtest_main
)

gtest_discover_tests(test_strategy)
