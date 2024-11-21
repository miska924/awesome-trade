#pragma once

#include <vector>
#include <util/vector_view/vector_view.h>
#include <algorithm>
#include <stdexcept>
#include <ostream>


template<typename T>
class TSumQueue {
    std::vector<T> values1;
    std::vector<T> values2;
    std::vector<T> sums1;
    std::vector<T> sums2;
public:
    TSumQueue() = default;

    size_t Size() const {
        return values1.size() + values2.size();
    }

    void Push(T value) {
        values1.push_back(value);
        sums1.push_back(sums1.empty() ? value : sums1.back() + value);
    }

    T Pop() {
        if (values1.empty() && values2.empty()) {
            throw std::out_of_range("Queue is empty");
        }
        if (values2.empty()) {
            while (!values1.empty()) {
                values2.push_back(values1.back());

                values1.pop_back();
                sums1.pop_back();

                sums2.push_back(sums2.empty() ? values2.back() : sums2.back() + values2.back());
            }
        }
        T result = values2.back();
        values2.pop_back();
        sums2.pop_back();
        return result;
    }

    void Clear() {
        values1.clear();
        values2.clear();
        sums1.clear();
        sums2.clear();
    }

    T operator()() const {
        T result = static_cast<T>(0);
        if (!sums1.empty()) {
            result = sums1.back();
        }
        if (!sums2.empty()) {
            result += sums2.back();
        }
        return result;
    }

    friend std::ostream& operator<<(std::ostream& os, const TSumQueue<T>& queue) {
        os << "Values:\t";
        for (int i = queue.values2.size(); i > 0; --i) {
            os << queue.values2[i - 1] << "\t";
        }
        os << "|\t";
        for (const T& value : queue.values1) {
            os << value << "\t";
        }
        os << "\nSums  :\t";
        for (int i = queue.sums2.size(); i > 0; --i) {
            os << queue.sums1[i - 1] << "\t";
        }
        os << "|\t";
        for (const T& value : queue.sums1) {
            os << value << "\t";
        }
        os << std::endl;
        return os;
    }
};
