add_library(dummy_optimizer optimizer.cpp)

target_link_libraries(
    dummy_optimizer
    PRIVATE
)

add_subdirectory(ut)
