#pragma once
#include "math_api.hpp"

namespace intern {
    struct Transform {
        Transform();
        Transform(Vec3f pos);
        Transform(Vec3f pos, Vec3f rot);
        Transform(Vec3f pos, Vec3f rot, Vec3f scale);
        void reset();

        Vec3f pos;
        Vec3f rot;
        Vec3f scale;
    };

    Mat4f transformation_matrix(const Transform& transform);
}