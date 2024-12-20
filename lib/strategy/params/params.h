#pragma once

#include <stdexcept>
#include <string>
#include <utility>
#include <variant>
#include <vector>


template<typename T>
struct TRange {
    T min;
    T max;
    T step;

    bool Contains(T value) {
        return min <= value && value <= max;
    }

    bool operator==(const TRange<T>& other) const {
        return min == other.min && max == other.max && step == other.step;
    }
};

template<typename T>
struct TLinearRange: TRange<T> {
    TLinearRange(T min, T max, T step): TRange<T>{min, max, step} {}
    T Next(T value) {
        return value + TRange<T>::step;
    }
};

template<typename T>
struct TLogRange: TRange<T> {
    TLogRange(T min, T max, T step): TRange<T>{min, max, step} {}
    T Next(T value) {
        return value * TRange<T>::step;
    }
};

class TParams;

using TParam = std::variant<
    int,
    double,
    TLinearRange<int>,
    TLinearRange<double>,
    TLogRange<int>,
    TLogRange<double>,
    TParams
>;

bool operator==(const TParam& left, const TParam& right);

class TParams {
friend std::hash<TParams>;
public:
    TParams();
    TParams(std::initializer_list<std::pair<std::string, TParam>> params);

    const TParam& operator[](const std::string& name) const;
    const TParam& operator[](size_t index) const;

    TParams operator+(const TParams& other) const;
    bool operator==(const TParams& other) const;

private:
    std::vector<std::pair<std::string, TParam>> params;
};
