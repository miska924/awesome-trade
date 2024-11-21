#pragma once

#include <iostream>

#include <strategy/closers/closer.h>
#include <strategy/openers/opener.h>
#include <strategy/params/params.h>
#include <strategy/signals.h>

struct IStrategy {
    virtual ESignal Signal(TVectorView<TCandle> candles) = 0;
};

template <Opener TOpener, Closer TCloser>
class TStrategy : public IStrategy {
public:
    TStrategy(const TParams& params)
        : opener(std::get<TParams>(params["opener"]))
        , closer(std::get<TParams>(params["closer"])) {}

    ESignal Signal(TVectorView<TCandle> candles) override {
        EOpenSignal openSignal = opener.Signal(candles);
        ECloseSignal closeSignal = closer.Signal(candles, signal);
        // если я в позиции, то можно закрываться, при условии, что новая позиция не будет открыта в ту же сторону
        if (signal != EOpenSignal::NONE && closeSignal == ECloseSignal::CLOSE && openSignal != signal) {
            signal = EOpenSignal::NONE;
            return ESignalFrom(closeSignal);
        }
        // иначе, если я не в позиции, то можно открываться
        if (signal == EOpenSignal::NONE) {
            signal = openSignal;
            return ESignalFrom(signal);
        }
        // если ничего не вышло, то ничего не делаю
        return ESignal::NONE;
    }

private:
    TOpener opener;
    TCloser closer;
    EOpenSignal signal = EOpenSignal::NONE;
};

template <typename T>
concept Strategy = std::derived_from<T, IStrategy>;
