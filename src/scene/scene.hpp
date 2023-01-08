#pragma once
#include "scene_object.hpp"
#include "scene_container.hpp"

namespace intern {
    struct Scene : public ObjID, public SceneContainer {
    public:
        Scene(const string& name = "Scene");

        void set_main_camera(SceneObject& cam_obj);
        SceneObject& get_main_camera();
        const SceneObject& get_main_camera() const;

        string name;
    private:
        SceneObject* m_main_camera;
    };
}