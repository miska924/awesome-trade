#include <gtest/gtest.h>

#include <vector>

#include <markets/market.h>
#include <strategy/features/sma/feature.h>
#include <util/vector_view/vector_view.h>


const double EPS = 1e-6;


const std::vector<TCandle> candles = {
    {.time = 1, .close = 1},
    {.time = 2, .close = 2},
    {.time = 3, .close = 3},
    {.time = 4, .close = 4},
    {.time = 5, .close = 5},
    {.time = 6, .close = 6},
};


template<Feature TFeature>
void TestSmaFeature() {
    const int PERIOD = 3;

    TFeature feature({{"period", PERIOD}});

    std::vector<double> expected = {2, 3, 4, 5};
    for (size_t i = PERIOD; i < candles.size(); ++i) {
        if (i < PERIOD) {
            EXPECT_THROW(feature(TVectorView(candles).SubView(0, i)), std::invalid_argument);
        } else {
            EXPECT_NEAR(expected[i - PERIOD], feature(TVectorView(candles).SubView(0, i)), EPS);
        }
    }
}


TEST(SmaFeature, Naive) {
    TestSmaFeature<TNaiveSmaFeature>();
}

TEST(SmaFeature, Smart) {
    TestSmaFeature<TSmaFeature<2>>();
}
