#include <gtest/gtest.h>

#include <strategy/openers/cross/opener.h>
#include <strategy/features/dummy/feature.h>
#include <strategy/params/params.h>


TEST(CrossOpener, TestConstruction) {
    TCrossOpener<TDummyFeature> opener({
        {"fast", TParams{}},
        {"slow", TParams{}},
    });
}
