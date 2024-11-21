#include <gtest/gtest.h>

#include <vector>

#include <strategy/features/dummy/feature.h>


TEST(DummyFeature, TestConstruction) {
    TDummyFeature feature({});

    std::vector<TCandle> candles = {
        {.time = 1, .close = 10},
    };

    ASSERT_EQ(feature(candles), 10);
}
