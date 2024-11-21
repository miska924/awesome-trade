add_library(sma_feature feature.cpp)

target_link_libraries(
    sma_feature
    PRIVATE
    feature
    sum_queue
    macros
)

add_subdirectory(ut)
