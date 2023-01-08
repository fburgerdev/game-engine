#include "projection.hpp"
#include "debug_api.hpp"
#include "scene_api.hpp"

namespace intern {
    Mat4f create_view_matrix(const Transform& transform) {
        Mat4f rot_mat = transposed(rotation_matrix(transform.rot));
        Mat4f trans_mat = translation_matrix(-transform.pos);
        return rot_mat * trans_mat;
    }
    Mat4f create_perspective_projection_matrix(f32 fov, Vec2f z_range, f32 aspect_ratio) {
        const f32 tan_fov = 1.0f / tan(fov / 2);
        Mat4f proj_mat = zeros<f32, 4>();
        proj_mat.at(0, 0) = tan_fov;
        proj_mat.at(1, 1) = tan_fov * aspect_ratio;

        // clip z to [0, 1]
        // proj_mat.at(2, 2) = z_range.y / (z_range.y - z_range.x);
        // proj_mat.at(2, 3) = -z_range.x * z_range.y / (z_range.y - z_range.x);
        
        // clip z to [-1, 1] for OPENGL
        proj_mat.at(2, 2) = 2 * z_range.y / (z_range.y - z_range.x) - 1;
        proj_mat.at(2, 3) = -2 * z_range.x * z_range.y / (z_range.y - z_range.x);

        proj_mat.at(3, 2) = 1;

        return proj_mat;
    }
    Mat4f create_orthographic_projection_matrix(f32 scale, Vec2f z_range, f32 aspect_ratio) {
        Mat4f proj_mat = zeros<f32, 4>();
        proj_mat.at(0, 0) = 1 / scale;
        proj_mat.at(1, 1) = aspect_ratio / scale;

        // clip z to [0, 1]
        // proj_mat.at(2, 2) = 1 / (z_range.y - z_range.x);
        // proj_mat.at(2, 3) = -z_range.x / (z_range.y - z_range.x);

        // clip z to [-1, 1] for OPENGL
        proj_mat.at(2, 2) = 2 / (z_range.y - z_range.x);
        proj_mat.at(2, 3) = - 2 * z_range.x / (z_range.y - z_range.x) - 1;

        proj_mat.at(3, 3) = 1;

        return proj_mat;
    }
    Mat4f create_view_projection_matrix(const SceneObject& camera_obj, f32 aspect_ratio) {
        Mat4f proj_mat = zeros<f32, 4>();
        const Camera& camera = camera_obj.get_camera();
        if (camera.mode == CameraMode::Perspective) {
            proj_mat = create_perspective_projection_matrix(camera.perspective.fov, camera.perspective.z_range, aspect_ratio);
        }
        else if (camera.mode == CameraMode::Orthographic) {
            proj_mat = create_orthographic_projection_matrix(camera.orthographic.scale, camera.orthographic.z_range, aspect_ratio);
        }
        return proj_mat * create_view_matrix(camera_obj.transform);
    }

    void projection3D_scene_obj_draw_prepare(const Scene& scene, const SceneObject& scene_obj, Material& material) {
        f32 aspect_ratio = 1.5f;
        material.set_mat4f("u_mvp", create_view_projection_matrix(scene.get_main_camera(), aspect_ratio) * transformation_matrix(scene_obj.transform));
        material.set_mat4f("u_rot", rotation_matrix(scene_obj.transform.rot));
    }
}