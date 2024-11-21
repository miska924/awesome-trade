add_executable(test_dummy_runner test_runner.cpp)

target_link_libraries(
    test_dummy_runner
    PRIVATE
    runner
    backtest_market
    strategy
    dummy_opener
    dummy_closer
    GTest::gtest_main
)

gtest_discover_tests(test_dummy_runner)
