#include <gtest/gtest.h>

#include <strategy/closers/cross/closer.h>
#include <strategy/features/dummy/feature.h>


TEST(CrossCloser, TestConstruction) {
    TCrossCloser<TDummyFeature> closer({
        {"fast", TParams{}},
        {"slow", TParams{}},
    });
}
