add_library(optimizer optimizer.cpp)

target_link_libraries(
    optimizer
    PRIVATE
)

add_subdirectory(dummy)
