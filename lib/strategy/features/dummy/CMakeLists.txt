add_library(dummy_feature feature.cpp)

target_link_libraries(
    dummy_feature
PRIVATE
    feature
    params
    macros
    vector_view
)

add_subdirectory(ut)
