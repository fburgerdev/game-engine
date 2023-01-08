#pragma once
#include "component.hpp"
#include "math_api.hpp"

namespace intern {
    enum class CameraMode {
        Perspective, Orthographic
    };
    struct Camera : public Component {
        Camera(CameraMode mode)
            : Component(ComponentType::Camera), mode(mode) {}
        Camera()
            : Component(ComponentType::Camera) {}

        CameraMode mode;
        union {
            struct {
                f32 fov;
                Vec2f z_range;
            } perspective;
            struct {
                f32 scale;
                Vec2f z_range; 
            } orthographic;
        };
    };
    Camera create_perspective_camera(f32 fov = PI_HALFS, Vec2f z_range = Vec2f(0.1f, 10000.0f));
    Camera create_orthographic_camera(f32 scale = 10, Vec2f z_range = Vec2f(0.1f, 10000.0f));
}