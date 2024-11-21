add_library(dummy_closer closer.cpp)

target_link_libraries(
    dummy_closer
    PRIVATE
    closer
    macros
)

add_subdirectory(ut)
