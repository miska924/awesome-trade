add_library(market market.cpp recorders.cpp)

target_link_libraries(
    market
    PRIVATE
    jsoncpp
    http_client
)

add_subdirectory(ut)
add_subdirectory(backtest)
add_subdirectory(tinkoff)
