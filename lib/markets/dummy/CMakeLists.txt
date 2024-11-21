add_library(dummy_market market.cpp)

target_link_libraries(
    dummy_market
    PRIVATE
    market
)

add_subdirectory(ut)
