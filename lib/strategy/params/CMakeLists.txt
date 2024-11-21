add_library(params params.cpp)

target_link_libraries(
    params
    PRIVATE
)

add_subdirectory(ut)
