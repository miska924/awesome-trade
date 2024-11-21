add_library(strategy strategy.cpp)
add_library(signals signals.cpp)

target_link_libraries(
    strategy
    PRIVATE
    params
    signals
)

add_subdirectory(closers)
add_subdirectory(features)
add_subdirectory(openers)
add_subdirectory(optimizers)
add_subdirectory(params)
add_subdirectory(ut)
