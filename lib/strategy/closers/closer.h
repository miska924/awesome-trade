#pragma once

#include <concepts>

#include <markets/market.h>
#include <util/vector_view/vector_view.h>
#include <strategy/signals.h>


class ICloser {
public:
    virtual ECloseSignal Signal(TVectorView<TCandle> candles, EOpenSignal signal) = 0;
};

template<typename T>
concept Closer = std::derived_from<T, ICloser>;
