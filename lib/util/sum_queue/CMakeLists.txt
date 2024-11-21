add_library(sum_queue sum_queue.cpp)

target_link_libraries(
    sum_queue
PRIVATE
)

add_subdirectory(ut)
