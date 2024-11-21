add_executable(perf_sma_open_close_strategy perf_sma_open_close_strategy.cpp)

target_link_libraries(
    perf_sma_open_close_strategy
PRIVATE
    strategy
    cross_opener
    cross_closer
    sma_feature
    params
    vector_view
)