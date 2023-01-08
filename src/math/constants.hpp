#pragma once
#include "common.hpp"

namespace intern {
    inline constexpr f32 PI = 3.1415926f;
    inline constexpr f32 TAU = 2 * PI;
    inline constexpr f32 PI_HALFS = PI / 2;

    inline constexpr f32 DEG_0 = 0;
    inline constexpr f32 DEG_90 = PI_HALFS;
    inline constexpr f32 DEG_180 = PI;
    inline constexpr f32 DEG_270 = 3 * PI / 4;
    inline constexpr f32 DEG_360 = TAU;

    inline constexpr f32 EULER = 2.7182818f;
    inline constexpr f32 EULER_HALFS = EULER / 2;

    inline constexpr f32 GOLDEN_RATIO = 1.618033f;
}