#pragma once

#include <iostream>
#include <util/vector_view/vector_view.h>

#include <markets/market.h>
#include <strategy/features/feature.h>
#include <strategy/openers/opener.h>
#include <strategy/params/params.h>


template<Feature TFeature>
class TCrossOpener : public IOpener {
public:
    TCrossOpener(const TParams& params)
        : fastFeature(std::get<TParams>(params["fast"]))
        , slowFeature(std::get<TParams>(params["slow"])) {}

    EOpenSignal Signal(TVectorView<TCandle> candles) override {
        if (!candles.Back().full) {
            return EOpenSignal::NONE;
        }

        TVectorView<TCandle> prev = candles.SubView(0, candles.Size() - 1);
        if (fastFeature(prev) < slowFeature(prev) && fastFeature(candles) > slowFeature(candles)) {
            return EOpenSignal::BUY;
        } else if (fastFeature(prev) > slowFeature(prev) && fastFeature(candles) < slowFeature(candles)) {
            return EOpenSignal::SELL;
        }

        return EOpenSignal::NONE;
    }
private:
    TFeature fastFeature;
    TFeature slowFeature;
};
