add_library(feature feature.cpp feature.cpp)

target_link_libraries(
    feature
PRIVATE
    market
    params
)

add_subdirectory(dummy)
add_subdirectory(sma)
