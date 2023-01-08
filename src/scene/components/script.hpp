#pragma once
#include "component.hpp"
#include "scene/transform.hpp"
#include "event_api.hpp"
#include "utils/time.hpp"

namespace intern {
    struct SceneObject;
    class Script {
    public:
        Script(SceneObject& scene_obj);

        virtual void on_update(Timestep ts) {}
        virtual void on_event(Event e) {}

        Transform& transform;
        SceneObject& scene_obj;
    };
}