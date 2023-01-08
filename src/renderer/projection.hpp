#pragma once
#include "scene_api.hpp"
#include "material.hpp"

namespace intern {
    Mat4f create_view_matrix(const Transform& transform);
    Mat4f create_perspective_projection_matrix(f32 fov, Vec2f z_range, f32 aspect_ratio);
    Mat4f create_orthographic_projection_matrix(f32 scale, Vec2f z_range, f32 aspect_ratio);
    Mat4f create_view_projection_matrix(const SceneObject& camera_obj, f32 aspect_ratio);

    void projection3D_scene_obj_draw_prepare(const Scene& scene, const SceneObject& scene_obj, Material& material);
}