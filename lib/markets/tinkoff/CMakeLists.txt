add_library(tinkoff_market market.cpp)

target_link_libraries(
    tinkoff_market
    PRIVATE
    market
)

add_subdirectory(ut)
