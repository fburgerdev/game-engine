#include "transform3d.hpp"
#include "arithmetic.hpp"

namespace intern {
    Mat4f translation_matrix(const Vec3f& pos) {
        Mat4f out = identity<f32, 4>();
        out.at(0, 3) = pos.x;
        out.at(1, 3) = pos.y;
        out.at(2, 3) = pos.z;
        return out;
    }
    Mat4f rotation_matrix(const Vec3f& rot) {
        Mat4f out = zeros<f32, 4>();
        f32 sina = sin(rot.y);
        f32 cosa = cos(rot.y);
        f32 sinb = sin(rot.x);
        f32 cosb = cos(rot.x);
        f32 sinc = sin(rot.z);
        f32 cosc = cos(rot.z);

        out.at(0, 0) = cosa * cosc + sina * sinc * sinb;
        out.at(0, 1) = cosa * sinc - sina * sinb * cosc;
        out.at(0, 2) = sina * cosb;

        out.at(1, 0) = -sinc * cosb;
        out.at(1, 1) = cosb * cosc;
        out.at(1, 2) = sinb;

        out.at(2, 0) = -sina * cosc + cosa * sinc * sinb;
        out.at(2, 1) = -sina * sinc - cosa * sinb * cosc;
        out.at(2, 2) = cosa * cosb;

        out.at(3, 3) = 1;
        return out;
    }
    Mat4f scale_matrix(const Vec3f& scale) {
        Mat4f out = zeros<f32, 4>();
        out.at(0, 0) = scale.x;
        out.at(1, 1) = scale.y;
        out.at(2, 2) = scale.z;
        out.at(3, 3) = 1;
        return out;
    }

    Vec3f rotate(const Vec3f& vec, const Vec3f& rot) {
        return Vec3f(rotation_matrix(rot) * Vec4f(vec, 0));
    }
}