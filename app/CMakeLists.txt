add_executable(app app.cpp)

target_link_libraries(
    app
PRIVATE
    strategy
    cross_opener
    cross_closer
    sma_feature
    params
    vector_view
)