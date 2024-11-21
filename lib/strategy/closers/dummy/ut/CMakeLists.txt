add_executable(test_dummy_closer test_closer.cpp)

target_link_libraries(
    test_dummy_closer
PRIVATE
    dummy_closer
    params
    GTest::gtest_main
)

gtest_discover_tests(test_dummy_closer)
