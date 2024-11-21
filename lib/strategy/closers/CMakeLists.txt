add_library(closer closer.cpp)

target_link_libraries(
    closer
PRIVATE
    signals
    vector_view
    market
)

add_subdirectory(dummy)
add_subdirectory(cross)
