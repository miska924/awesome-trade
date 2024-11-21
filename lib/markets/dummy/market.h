#pragma once

#include <markets/market.h>


class TDummyMarket : IMarket {
public:
    TInstrument GetInstrument() override {
        return {
            .lotSize = 1,
            .market = *this
        };
    }
};