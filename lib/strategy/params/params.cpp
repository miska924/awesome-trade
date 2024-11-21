#include <strategy/params/params.h>
#include <strategy/params/hash.h>

#include <algorithm>


TParams::TParams() {}
TParams::TParams(std::initializer_list<std::pair<std::string, TParam>> params): params(params) {
    // std::sort(params.begin(), params.end(), [](const auto& a, const auto& b) {
    //     return a.first < b.first;
    // });
}

const TParam& TParams::operator[](const std::string& name) const {
    for (const auto& param : params) {
        if (param.first == name) {
            return param.second;
        }
    }
    throw std::out_of_range("Parameter not found");
}

const TParam& TParams::operator[](size_t index) const {
    if (index >= params.size()) {
        throw std::out_of_range("Index out of range");
    }
    return (params.begin() + index)->second;
}

TParams TParams::operator+(const TParams& other) const {
    TParams result = *this;
    result.params.insert(result.params.end(), other.params.begin(), other.params.end());
    // TParams result;
    // std::merge(params.begin(), params.end(), other.params.begin(), other.params.end(), std::back_inserter(result.params), [](const auto& a, const auto& b) {
    //     return a.first < b.first;
    // });
    return result;
}

bool TParams::operator==(const TParams& other) const {
    if (params.size() != other.params.size()) {
        return false;
    }
    for (size_t i = 0; i < params.size(); ++i) {
        if (params.at(i) != other.params.at(i)) {
            return false;
        }
    }
    return true;
}

bool operator==(const TParam& left, const TParam& right) {
    if (std::holds_alternative<int>(left) && std::holds_alternative<int>(right)) {
        return std::get<int>(left) == std::get<int>(right);
    } else if (std::holds_alternative<double>(left) && std::holds_alternative<double>(right)) {
        return std::get<double>(left) == std::get<double>(right);
    } else if (std::holds_alternative<TLinearRange<int>>(left) && std::holds_alternative<TLinearRange<int>>(right)) {
        return std::get<TLinearRange<int>>(left) == std::get<TLinearRange<int>>(right);
    } else if (std::holds_alternative<TLinearRange<double>>(left) && std::holds_alternative<TLinearRange<double>>(right)) {
        return std::get<TLinearRange<double>>(left) == std::get<TLinearRange<double>>(right);
    } else if (std::holds_alternative<TLogRange<int>>(left) && std::holds_alternative<TLogRange<int>>(right)) {
        return std::get<TLogRange<int>>(left) == std::get<TLogRange<int>>(right);
    } else if (std::holds_alternative<TLogRange<double>>(left) && std::holds_alternative<TLogRange<double>>(right)) {
        return std::get<TLogRange<double>>(left) == std::get<TLogRange<double>>(right);
    } else if (std::holds_alternative<TParams>(left) && std::holds_alternative<TParams>(right)) {
        return std::get<TParams>(left) == std::get<TParams>(right);
    }
    return false;
}
