add_library(market market.cpp)

target_link_libraries(
    market
    PRIVATE
)

add_subdirectory(ut)
add_subdirectory(backtest)
add_subdirectory(tinkoff)
add_subdirectory(dummy)
