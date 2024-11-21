#pragma once

#include <util/vector_view/vector_view.h>
#include <concepts>
#include <unordered_map>

#include <markets/market.h>
#include <strategy/params/params.h>


class IFeature;

template<typename T>
concept Feature = std::derived_from<T, IFeature>;

class IFeature {
public:
    virtual double operator()(TVectorView<TCandle> candles) const = 0;
};
