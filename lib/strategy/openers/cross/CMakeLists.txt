add_library(cross_opener opener.cpp)

target_link_libraries(
    cross_opener
PRIVATE
    opener
)

add_subdirectory(ut)
