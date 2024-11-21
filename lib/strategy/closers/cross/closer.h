#pragma once

#include <util/vector_view/vector_view.h>

#include <markets/market.h>
#include <strategy/features/feature.h>
#include <strategy/closers/closer.h>
#include <strategy/params/params.h>


template<Feature TFeature>
class TCrossCloser : public ICloser {
public:
    TCrossCloser(const TParams& params)
        : fastFeature(std::get<TParams>(params["fast"]))
        , slowFeature(std::get<TParams>(params["slow"])) {}

    ECloseSignal Signal(TVectorView<TCandle> candles, EOpenSignal signal) override {
        if (!candles.Back().full) {
            return ECloseSignal::NONE;
        }

        if ((fastFeature(candles) > slowFeature(candles) && signal == EOpenSignal::SELL)
         || (fastFeature(candles) < slowFeature(candles) && signal == EOpenSignal::BUY)) {
            return ECloseSignal::CLOSE;
        }

        return ECloseSignal::NONE;
    }
private:
    TFeature fastFeature;
    TFeature slowFeature;
};
