add_library(cross_closer closer.cpp)

target_link_libraries(
    cross_closer
PRIVATE
    closer
)

add_subdirectory(ut)
