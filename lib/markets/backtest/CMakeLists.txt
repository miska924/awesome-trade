add_library(backtest_market market.cpp)

target_link_libraries(
    backtest_market
    PRIVATE
    market
)

add_subdirectory(ut)
