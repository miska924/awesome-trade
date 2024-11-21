add_library(opener opener.cpp)

target_link_libraries(
    opener
PRIVATE
    signals
    vector_view
    market
)

add_subdirectory(dummy)
add_subdirectory(cross)
