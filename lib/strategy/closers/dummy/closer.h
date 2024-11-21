#pragma once

#include <strategy/closers/closer.h>
#include <strategy/params/params.h>
#include <util/macros/macros.h>


class TDummyCloser : public ICloser {
public:
    TDummyCloser(const TParams& params) {
        UNUSED(params);
    }

    ECloseSignal Signal(TVectorView<TCandle> candles, EOpenSignal signal) override {
        UNUSED(candles);
        UNUSED(signal);
        return ECloseSignal::CLOSE;
    }
};
