#pragma once

#include <iostream>

#include <strategy/closers/closer.h>
#include <strategy/openers/opener.h>
#include <strategy/params/params.h>
#include <strategy/signals.h>

struct IStrategy {
    virtual ~IStrategy() = default;
    virtual ESignal Signal(TVectorView<TCandle> candles) = 0;
};

template <Opener TOpener, Closer TCloser>
class TStrategy: public IStrategy {
public:
    TStrategy(const TParams& params)
        : opener(std::get<TParams>(params["opener"]))
        , closer(std::get<TParams>(params["closer"])) {}

    // ESignal Signal(TVectorView<TCandle> candles) override {
    //     if (signal != EOpenSignal::NONE) {
    //         signal = opener.Signal(candles);
    //         return ESignalFrom(signal);
    //     }
    //     ECloseSignal closeSignal = closer.Signal(candles, signal);
    //     if (closeSignal != ECloseSignal::NONE) {
    //         signal = EOpenSignal::NONE;
    //     }
    //     return ESignalFrom(closeSignal);
    // }

    ESignal Signal(TVectorView<TCandle> candles) override {
        EOpenSignal openSignal = opener.Signal(candles);
        ECloseSignal closeSignal = closer.Signal(candles, signal);
        if (signal != EOpenSignal::NONE) {
            signal = openSignal;
            return ESignalFrom(signal);
        }
        if (closeSignal != ECloseSignal::NONE) {
            signal = EOpenSignal::NONE;
        }
        return ESignalFrom(closeSignal);
    }

    ~TStrategy() override = default;
private:
    TOpener opener;
    TCloser closer;
    EOpenSignal signal = EOpenSignal::NONE;
};

template <typename T>
concept Strategy = std::derived_from<T, IStrategy>;
