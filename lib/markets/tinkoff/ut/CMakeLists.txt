add_executable(test_tinkoff_market test_market.cpp)

target_link_libraries(
    test_tinkoff_market
    PRIVATE
    tinkoff_market
    GTest::gtest_main
)

gtest_discover_tests(test_tinkoff_market)
