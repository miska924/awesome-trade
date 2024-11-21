add_executable(test_market test_market.cpp)

target_link_libraries(
    test_market
    PRIVATE
    market
    GTest::gtest_main
)

gtest_discover_tests(test_market)
