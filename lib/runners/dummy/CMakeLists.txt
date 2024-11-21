add_library(dummy_runner runner.cpp)

target_link_libraries(
    dummy_runner
    PRIVATE
    runner
)

add_subdirectory(ut)
