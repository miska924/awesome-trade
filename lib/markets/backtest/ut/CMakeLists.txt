add_executable(test_backtest_market test_market.cpp)

target_link_libraries(
    test_backtest_market
    PRIVATE
    backtest_market
    GTest::gtest_main
)

gtest_discover_tests(test_backtest_market)
