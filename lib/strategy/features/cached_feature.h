#pragma once

#include <stdexcept>
#include <unordered_map>
#include <utility>

#include <strategy/features/feature.h>
#include <strategy/params/hash.h>
#include <strategy/params/params.h>
#include <util/vector_view/vector_view.h>


bool operator==(const std::pair<TParams, TCandle>& left, const std::pair<TParams, TCandle>& right) {
    return left.first == right.first && left.second == right.second;
}

namespace std {
    template<>
    struct hash<std::pair<TParams, TCandle>> {
        size_t operator()(const std::pair<TParams, TCandle>& obj) const {
            return hash<TParams>()(obj.first) ^ hash<TCandle>()(obj.second);
        }
    };
}

template<Feature TFeature>
class TCachedFeature : public IFeature {
public:
    TCachedFeature(const TParams& params) : feature(params), params(params) {}

    double operator()(TVectorView<TCandle> candles) const override {
        if (candles.Size() == 0) {
            throw std::invalid_argument("empty candles");
        }

        std::pair<TParams, TCandle> key(params, candles.Back());
        if (auto it = cache.find(key); it != cache.end()) {
            return it->second;
        }
        return cache[key] = feature(candles);
    }
private:
    TFeature feature;
    TParams params;
    static std::unordered_map<std::pair<TParams, TCandle>, double> cache;
};

template<Feature TFeature>
std::unordered_map<std::pair<TParams, TCandle>, double> TCachedFeature<TFeature>::cache = {};
