#include <strategy/params/params.h>

#include <algorithm>


TParams::TParams() {}
TParams::TParams(
    std::initializer_list<std::pair<std::string, TParam>> params
): params(params) {

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
