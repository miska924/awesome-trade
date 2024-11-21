#pragma once

#include <stdexcept>
#include <vector>


template <class T>
class TVectorView {
public:
    TVectorView() = delete;
    TVectorView(const std::vector<T>& vector)
        : v(vector)
        , begin(0)
        , sz(vector.size()) {}

    TVectorView(const std::vector<T>& vector, size_t offset, size_t count)
        : v(vector)
        , begin(offset)
        , sz(count)
    {
        if (sz > vector.size()) {
            throw std::invalid_argument("Invalid range");
        }
    }

    TVectorView(const TVectorView<T>& other)
        : v(other.v)
        , begin(other.begin)
        , sz(other.sz) {}

    size_t Size() const {
        return sz;
    }

    const T& operator[](size_t i) const {
        if (i >= sz) {
            throw std::out_of_range("Index out of range");
        }
        return v[begin + i];
    }

    TVectorView<T> SubView(size_t offset, size_t count) const {
        if (offset + count > sz) {
            throw std::invalid_argument("Invalid range");
        }
        return TVectorView<T>(v, begin + offset, count);
    }

    std::vector<T> ToVector() const {
        return std::vector<T>(v.begin() + begin, v.begin() + begin + sz);
    }

    const T& Back() const {
        if (sz == 0) {
            throw std::out_of_range("TVectorView is empty");
        }
        return v[begin + sz - 1];
    }

    TVectorView<T>& operator=(const TVectorView<T>& other) {
        TVectorView<T> tmp(other);
        std::swap(*this, tmp);
        return *this;
    }

    TVectorView<T> operator=(const TVectorView<T>& other) const {};
private:
    const std::vector<T>& v;
    size_t begin;
    size_t sz;
};
