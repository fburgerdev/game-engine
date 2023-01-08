#pragma once
#include "matrix.hpp"

namespace intern {
    // alias
    template<typename T, adress N>
    using Vec = Mat<T, N, 1>;
    template<typename T>
    using Vec2 = Vec<T, 2>;
    template<typename T>
    using Vec3 = Vec<T, 3>;
    template<typename T>
    using Vec4 = Vec<T, 4>;

    using Vec2f = Vec2<f32>;
    using Vec3f = Vec3<f32>;
    using Vec4f = Vec4<f32>;

    using Vec2d = Vec2<f64>;
    using Vec3d = Vec3<f64>;
    using Vec4d = Vec4<f64>;

    using Vec2i = Vec2<i32>;
    using Vec3i = Vec3<i32>;
    using Vec4i = Vec4<i32>;
 
    using Vec2u = Vec2<u32>;
    using Vec3u = Vec3<u32>;
    using Vec4u = Vec4<u32>;

    using Vec2u8 = Vec2<u8>;
    using Vec3u8 = Vec3<u8>;
    using Vec4u8 = Vec4<u8>;

    // funcs
    template<typename T, adress N>
    T dot(const Vec<T, N>& v1, const Vec<T, N>& v2) {
        T out = 0;
        for (adress n = 0; n < N; ++n) {
            out += v1 * v2;
        }
        return out;
    }
    template<typename T, adress N>
    T dot(const Vec<T, N>& v) {
        return dot(v, v);
    }

    template<typename T>
    Vec3<T> cross(const Vec3<T>& v1, const Vec3<T>& v2) {
        return Vec3<T>(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
    }
}