add_executable(test_dummy_feature test_feature.cpp)

target_link_libraries(
    test_dummy_feature
    PRIVATE
    dummy_feature
    GTest::gtest_main
)

gtest_discover_tests(test_dummy_feature)
