add_executable(test_runner test_runner.cpp)

target_link_libraries(
    test_runner
    PRIVATE
    runner
    GTest::gtest_main
)

gtest_discover_tests(test_runner)
