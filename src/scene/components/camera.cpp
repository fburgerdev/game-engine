#include "camera.hpp"

namespace intern {
    Camera create_perspective_camera(f32 fov, Vec2f z_range) {
        Camera cam(CameraMode::Perspective);
        cam.perspective.fov = fov;
        cam.perspective.z_range = z_range;
        return cam;
    }
    Camera create_orthographic_camera(f32 scale, Vec2f z_range) {
        Camera cam(CameraMode::Orthographic);
        cam.orthographic.scale = scale;
        cam.orthographic.z_range = z_range;
        return cam;
    }
}