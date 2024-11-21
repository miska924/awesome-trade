add_executable(test_sma_feature test_feature.cpp)

target_link_libraries(
    test_sma_feature
    PRIVATE
    sma_feature
    feature
    market
    params
    vector_view
    GTest::gtest_main
)

gtest_discover_tests(test_sma_feature)
