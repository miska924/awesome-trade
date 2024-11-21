#pragma once

#include <iostream>
#include <optional>
#include <algorithm>

#include <strategy/features/feature.h>
#include <util/sum_queue/sum_queue.h>
#include <util/vector_view/vector_view.h>
#include <util/macros/macros.h>


class TNaiveSmaFeature : public IFeature {
public:
    TNaiveSmaFeature(const TParams& params);
    double operator()(TVectorView<TCandle> candles) const override;
private:
    size_t period;
};

template<size_t LRU_CACHE_SIZE = 2>
class TSmaFeature : public IFeature {
public:
    TSmaFeature(const TParams& params);
    ~TSmaFeature();
    double operator()(TVectorView<TCandle> candles) const override;
private:
    std::optional<double> FindInCache(time_t time) const;

    size_t period;
    mutable time_t lastTime = 0;
    mutable TSumQueue<double> sum;

    mutable std::array<std::pair<time_t, double>, LRU_CACHE_SIZE> cache;
    mutable size_t cacheWritePosition = 0;
    ON_DEBUG(
        mutable size_t cacheHits = 0;
        mutable size_t cacheMisses = 0;
        mutable size_t o1Hits = 0;
        mutable size_t o1Misses = 0;
    )
};

template<size_t LRU_CACHE_SIZE>
TSmaFeature<LRU_CACHE_SIZE>::TSmaFeature(const TParams& params)
    : period(std::get<int>(params["period"]))
{
    std::fill(cache.begin(), cache.end(), std::make_pair(0, 0.0));
}

template<size_t LRU_CACHE_SIZE>
TSmaFeature<LRU_CACHE_SIZE>::~TSmaFeature() {
    ON_DEBUG(
        std::cerr << "CACHE: "
                << static_cast<double>(cacheHits) / (cacheHits + cacheMisses) * 100
                << "%  O(1): "
                << static_cast<double>(o1Hits) / (o1Hits + o1Misses) * 100
                << "%" << std::endl;
    )
}

template<size_t LRU_CACHE_SIZE>
double TSmaFeature<LRU_CACHE_SIZE>::operator()(TVectorView<TCandle> candles) const {
    size_t sz = candles.Size();
    if (sz < period) {
        throw std::invalid_argument("Not enough candles");
    }

    const TCandle& last = candles.Back();

    if (auto result = FindInCache(last.time); result) {
        ON_DEBUG(cacheHits++);
        return *result;
    }
    ON_DEBUG(cacheMisses++);

    const TCandle& prev = candles[sz - 2];

    if (period > 1 && sz > 1 && prev.time == lastTime) {
        ON_DEBUG(o1Hits++);
        sum.Push(last.close);
        if (sum.Size() > period) {
            sum.Pop();
        }
    } else {
        ON_DEBUG(o1Misses++);
        sum.Clear();
        for (size_t i = 0; i < period; ++i) {
            sum.Push(candles[sz - period + i].close);
        }
    }

    lastTime = last.time;

    double result = sum() / period;

    cache[cacheWritePosition++] = {last.time, result};
    cacheWritePosition %= LRU_CACHE_SIZE;

    return result;
}

template<size_t LRU_CACHE_SIZE>
std::optional<double> TSmaFeature<LRU_CACHE_SIZE>::FindInCache(time_t time) const {
    for (const auto& [key, value] : cache) {
        if (key == time) {
            return value;
        }
    }
    return std::nullopt;
}
