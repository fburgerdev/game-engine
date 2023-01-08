#pragma once
#include "core_api.hpp"
#include "components/camera.hpp"
#include "components/render_object.hpp"
#include "components/script.hpp"
#include "transform.hpp"

namespace intern {
    class SceneObject : public ObjID {
    public:
        SceneObject(const string& name = "SceneObject");
        SceneObject(ObjID&& id, const string& name = "SceneObject");

        // component 
        bool has_component(ComponentType type) const;
        void remove_component(ComponentType type);

        // mesh
        // Mesh& attach_mesh(const List<Vertex3D>& vertices);
        // Mesh& get_mesh();
        // const Mesh& get_mesh() const;

        // render object
        RenderObject& attach_render_object(Mesh& mesh, Material& material);
        RenderObject& get_render_object();
        const RenderObject& get_render_object() const;

        // camera
        Camera& attach_camera(const Camera& cam);
        Camera& get_camera();
        const Camera& get_camera() const;

        // script
        void attach_script(const string& name);
        template<typename T>
        T& attach_script() {
            Script* script = new T(*this);
            m_scripts[typeid(T).hash_code()] = script;
            return *static_cast<T*>(script);
        }
        template<typename T = Script>
        T& get_script() {
            return *static_cast<T*>(m_scripts.at(typeid(T).hash_code()));
        }
        template<typename T = Script>
        const T& get_script() const {
            return *static_cast<T*>(m_scripts.at(typeid(T).hash_code()));
        }
        Map<adress, Script*> get_scripts();
        const Map<adress, Script*> get_scripts() const;

        string name;
        Transform transform;
    private:
        Map<ComponentType, Component*> m_components;
        Map<adress, Script*> m_scripts;
    };
}