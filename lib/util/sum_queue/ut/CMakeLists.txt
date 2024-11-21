add_executable(test_sum_queue test_sum_queue.cpp)

target_link_libraries(
    test_sum_queue
PRIVATE
    sum_queue
    GTest::gtest_main
)

gtest_discover_tests(test_sum_queue)
