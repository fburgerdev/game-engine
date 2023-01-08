#include "scene_object.hpp"

namespace intern {
    SceneObject::SceneObject(const string& name)
        : ObjID(), name(name) {}
    SceneObject::SceneObject(ObjID&& id, const string& name)
        : ObjID(std::move(id)), name(name) {}

    bool SceneObject::has_component(ComponentType type) const {
        return m_components.find(type) != m_components.end();
    }
    void SceneObject::remove_component(ComponentType type) {
        delete m_components.at(type);
        m_components.erase(type);
    }

    // mesh
    // Mesh& SceneObject::attach_mesh(const List<Vertex3D>& vertices) {
    //     Mesh* mesh = new Mesh(vertices);
    //     m_components[ComponentType::Mesh] = mesh;
    //     return *mesh;
    // }
    // Mesh& SceneObject::get_mesh() {
    //     return *static_cast<Mesh*>(m_components.at(ComponentType::Mesh));
    // }
    // const Mesh& SceneObject::get_mesh() const {
    //     return *static_cast<Mesh*>(m_components.at(ComponentType::Mesh));
    // }

    // render object
    RenderObject& SceneObject::attach_render_object(Mesh& mesh, Material& material) {
        RenderObject* render_obj = new RenderObject(mesh, material);
        m_components[ComponentType::RenderObject] = render_obj;
        return *render_obj;
    }
    RenderObject& SceneObject::get_render_object() {
        return *static_cast<RenderObject*>(m_components.at(ComponentType::RenderObject));
    }
    const RenderObject& SceneObject::get_render_object() const {
        return *static_cast<RenderObject*>(m_components.at(ComponentType::RenderObject));
    }

    // camera
    Camera& SceneObject::attach_camera(const Camera& cam) {
        Camera* camera = new Camera(cam);
        m_components[ComponentType::Camera] = camera;
        return *camera;
    }
    Camera& SceneObject::get_camera() {
        return *static_cast<Camera*>(m_components.at(ComponentType::Camera));
    }
    const Camera& SceneObject::get_camera() const {
        return *static_cast<Camera*>(m_components.at(ComponentType::Camera));
    }

    // script
    std::pair<adress, Script*> create_script_from_string(const string& name, SceneObject& scene_obj); // defined in launch.cpp
    void SceneObject::attach_script(const string& name) {
        std::pair<adress, Script*> created = create_script_from_string(name, *this);
        m_scripts[created.first] = created.second;
    }
    Map<adress, Script*> SceneObject::get_scripts() {
        return m_scripts;
    }
    const Map<adress, Script*> SceneObject::get_scripts() const {
        return m_scripts;
    }
}