add_executable(test_vector_view test_vector_view.cpp)

target_link_libraries(
    test_vector_view
PRIVATE
    vector_view
    GTest::gtest_main
)

gtest_discover_tests(test_vector_view)
