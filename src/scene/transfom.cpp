#include "transform.hpp"
#include "debug_api.hpp"

namespace intern {
    Transform::Transform()
        : pos(0), rot(0), scale(1) {}
    Transform::Transform(Vec3f pos)
        : pos(pos), rot(0), scale(1) {}
    Transform::Transform(Vec3f pos, Vec3f rot)
        : pos(pos), rot(rot), scale(1) {}
    Transform::Transform(Vec3f pos, Vec3f rot, Vec3f scale)
        : pos(pos), rot(rot), scale(scale) {}

    void Transform::reset() {
        pos = Vec3f(0);
        rot = Vec3f(0);
        scale = Vec3f(1);
    }

    Mat4f transformation_matrix(const Transform& transform) {
        return translation_matrix(transform.pos) * scale_matrix(transform.scale) * rotation_matrix(transform.rot);
    }
}