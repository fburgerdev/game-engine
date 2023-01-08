#pragma once
#include "scene_api.hpp"
#include "debug_api.hpp"
#include "application_api.hpp"

namespace intern {
    class Cube : public Script {
    public:
        Cube(SceneObject& scene_obj) 
            : Script(scene_obj) {}

        virtual void on_update(Timestep ts) override {
            scene_obj.transform.pos.y = 5 + 2 * sin(Application::time().sec());
            scene_obj.transform.rot.x += 0.01;
            scene_obj.transform.rot.y += 0.025;
            scene_obj.transform.rot.z += 0.05;
        }
    };
}