#pragma once

#include <strategy/params/params.h>


namespace std {
    template<>
    struct hash<TLinearRange<int>> {
        size_t operator()(const TLinearRange<int>& obj) const {
            return std::hash<int>()(obj.min) ^ (std::hash<int>()(obj.max) << 1) ^ (std::hash<int>()(obj.step) << 2);
        }
    };

    template<>
    struct hash<TLinearRange<double>> {
        size_t operator()(const TLinearRange<double>& obj) const {
            return std::hash<double>()(obj.min) ^ (std::hash<double>()(obj.max) << 1) ^ (std::hash<double>()(obj.step) << 2);
        }
    };

    template<>
    struct hash<TLogRange<int>> {
        size_t operator()(const TLogRange<int>& obj) const {
            return std::hash<int>()(obj.min) ^ (std::hash<int>()(obj.max) << 1) ^ (std::hash<int>()(obj.step) << 2);
        }
    };

    template<>
    struct hash<TLogRange<double>> {
        size_t operator()(const TLogRange<double>& obj) const {
            return std::hash<double>()(obj.min) ^ (std::hash<double>()(obj.max) << 1) ^ (std::hash<double>()(obj.step) << 2);
        }
    };

    template<>
    struct hash<TParam> {
        size_t operator()(const TParam& obj) const {
            return std::visit([](const auto& value) -> size_t {
                using T = std::decay_t<decltype(value)>;
                if constexpr (std::is_same_v<T, int>) {
                    return std::hash<int>()(value);
                } else if constexpr (std::is_same_v<T, double>) {
                    return std::hash<double>()(value);
                } else if constexpr (std::is_same_v<T, TLinearRange<int>>) {
                    return std::hash<TLinearRange<int>>()(value);
                } else if constexpr (std::is_same_v<T, TLinearRange<double>>) {
                    return std::hash<TLinearRange<double>>()(value);
                } else if constexpr (std::is_same_v<T, TLogRange<int>>) {
                    return std::hash<TLogRange<int>>()(value);
                } else if constexpr (std::is_same_v<T, TLogRange<double>>) {
                    return std::hash<TLogRange<double>>()(value);
                } else if constexpr (std::is_same_v<T, TParams>) {
                    return std::hash<TParams>()(value);
                }
            }, obj);
        }
    };

    template<>
    struct hash<TParams> {
        size_t operator()(const TParams& obj) const {
            size_t result = 0;
            for (const auto& param : obj.params) {
                size_t h1 = hash<std::string>()(param.first);
                size_t h2 = hash<TParam>()(param.second);
                result ^= (h1 << 1) ^ (h2 << 2);
            }
            return result;
        }
    };
}
