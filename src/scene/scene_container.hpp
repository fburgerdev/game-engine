#pragma once
#include "scene_object.hpp"

namespace intern {
    struct SceneNode {
        ID parent;
        Set<ID> childs;
    };

    class SceneContainer {
    public:
        // create
        SceneObject& create_scene_obj(const SceneObject& parent);
        SceneObject& create_scene_obj(const string& name);
        SceneObject& create_scene_obj();

        // remove
        void remove_scene_obj(const SceneObject& obj);

        // parent
        void set_parent(const SceneObject& obj, const SceneObject& parent);
        SceneObject& get_parent(const SceneObject& obj);
        const SceneObject& get_parent(const SceneObject& obj) const;

        // access
        SceneObject& get_scene_obj(const string& name = "SceneObject");
        const SceneObject& get_scene_obj(const string& name = "SceneObject") const;
        Map<ID, SceneObject>& get_scene_objs();
        const Map<ID, SceneObject>& get_scene_objs() const;
    private:
        Map<ID, SceneNode> m_nodes;
        Map<ID, SceneObject> m_objs;
    };
}