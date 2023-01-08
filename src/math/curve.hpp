#pragma once
#include "vector.hpp"
#include "arithmetic.hpp"

namespace intern {
    template<typename T, adress N>
    Vec<T, N> lerp(const Vec<T, N>& from, const Vec<T, N>& to, T t) {
        return from * (1 - t) + to * t;
    }

    template<typename T, adress N>
    Vec<T, N> bezier(const Vec<T, N>& from, const Vec<T, N>& mid1, const Vec<T, N>& mid2, const Vec<T, N>& to, T t) {
        return from * pow3(1 - t) + mid1 * 3 * t * pow2(1 - t) + mid2 * 3 * pow2(t) * (1 - t) + to * pow3(t);
    }
}