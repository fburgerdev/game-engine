#pragma once
#include "vector.hpp"

namespace intern {
    Mat4f translation_matrix(const Vec3f& pos);
    Mat4f rotation_matrix(const Vec3f& rot);
    Mat4f scale_matrix(const Vec3f& scale);

    Vec3f rotate(const Vec3f& vec, const Vec3f& rot);
}