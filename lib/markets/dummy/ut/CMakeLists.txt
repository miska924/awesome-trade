add_executable(test_dummy_market test_market.cpp)

target_link_libraries(
    test_dummy_market
    PRIVATE
    dummy_market
    GTest::gtest_main
)

gtest_discover_tests(test_dummy_market)
