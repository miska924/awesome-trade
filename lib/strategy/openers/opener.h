#pragma once

#include <util/vector_view/vector_view.h>
#include <concepts>

#include <markets/market.h>
#include <strategy/signals.h>


struct IOpener {
    virtual ~IOpener() = default;
    virtual EOpenSignal Signal(TVectorView<TCandle> candles) = 0;
};

template<typename T>
concept Opener = std::derived_from<T, IOpener>;
