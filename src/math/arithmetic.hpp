#pragma once
#include "common.hpp"

namespace intern {
    i8 abs(i8 x);
    i16 abs(i16 x);
    i32 abs(i32 x);
    i64 abs(i64 x);
    f32 abs(f32 x);
    f64 abs(f64 x);

    f32 floor(f32 x);
    f64 floor(f64 x);
    f32 ceil(f32 x);
    f64 ceil(f64 x);

    f32 sin(f32 x);
    f64 sin(f64 x);
    f32 cos(f32 x);
    f64 cos(f64 x);
    f32 tan(f32 x);
    f64 tan(f64 x);
    f32 asin(f32 x);
    f64 asin(f64 x);
    f32 acos(f32 x);
    f64 acos(f64 x);
    f32 atan(f32 x);
    f64 atan(f64 x);

    f32 exp(f32 x);
    f64 exp(f64 x);
    f32 ln(f32 x);
    f64 ln(f64 x);
    f32 log2(f32 x);
    f64 log2(f64 x);
    f32 log10(f32 x);
    f64 log10(f64 x);
    f32 pow(f32 base, f32 exponent);
    f64 pow(f64 base, f64 exponent);
    f32 pow2(f32 x);
    f64 pow2(f64 x);
    f32 pow3(f32 x);
    f64 pow3(f64 x);
    
    template<typename T1, typename T2, typename... Rest>
    auto max(T1 val1, T2 val2, Rest... rest) {
        if constexpr(sizeof...(Rest) == 0) {
            return val1 < val2 ? val2 : val1;
        }
        else {
            return max(val1 < val2 ? val2 : val1, rest...);
        }
    }
    template<typename T1, typename T2, typename... Rest>
    auto min(T1 val1, T2 val2, Rest... rest) {
        if constexpr(sizeof...(Rest) == 0) {
            return val2 < val1 ? val2 : val1;
        }
        else {
            return max(val2 < val1 ? val2 : val1, rest...);
        }
    }
}