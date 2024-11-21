#pragma once

#include <concepts>


struct IRunner {
    virtual void Run() = 0;
};


template <typename T>
concept Runner = std::derived_from<T, IRunner>;
