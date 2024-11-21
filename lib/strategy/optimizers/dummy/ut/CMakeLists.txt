add_executable(test_dummy_optimizer test_optimizer.cpp)

target_link_libraries(
    test_dummy_optimizer
    PRIVATE
    dummy_optimizer
    GTest::gtest_main
)

gtest_discover_tests(test_dummy_optimizer)
