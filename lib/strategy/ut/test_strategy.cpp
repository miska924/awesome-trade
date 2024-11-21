#include <gtest/gtest.h>

#include <strategy/params/params.h>
#include <strategy/strategy.h>
#include <strategy/openers/dummy/opener.h>
#include <strategy/closers/dummy/closer.h>


TEST(Strategy, TestConstruction) {
    TStrategy<TDummyOpener, TDummyCloser> strategy({
        {"opener", TParams()},
        {"closer", TParams()},
    });
}
