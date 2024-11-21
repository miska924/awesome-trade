add_library(dummy_opener opener.cpp)

target_link_libraries(
    dummy_opener
    PRIVATE
    opener
    macros
)

add_subdirectory(ut)
