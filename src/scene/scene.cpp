#include "scene.hpp"

namespace intern {
    Scene::Scene(const string& name)
        : ObjID(), SceneContainer(), name(name), m_main_camera(nullptr) {} 

    void Scene::set_main_camera(SceneObject& cam_obj) {
        m_main_camera = &cam_obj;
    }
    SceneObject& Scene::get_main_camera() {
        return *m_main_camera;
    }
    const SceneObject& Scene::get_main_camera() const {
        return *m_main_camera;
    }
}