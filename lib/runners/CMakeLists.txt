add_library(runner runner.cpp)

target_link_libraries(
    runner
    PRIVATE
)

add_subdirectory(ut)
add_subdirectory(dummy)
