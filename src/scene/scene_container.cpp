#include "scene_container.hpp"

namespace intern {
     SceneObject& SceneContainer::create_scene_obj(const SceneObject& parent) {
        SceneObject& obj = emplace_in_map(m_objs);
        m_nodes[obj.get_id()].parent = parent.get_id();
        m_nodes[parent.get_id()].childs.insert(obj.get_id());
        return obj;
        return * new SceneObject();
    }
    SceneObject& SceneContainer::create_scene_obj(const string& name) {
        SceneObject& obj = emplace_in_map(m_objs, name);
        m_nodes[obj.get_id()].parent = 0;
        return obj;
    }
    SceneObject& SceneContainer::create_scene_obj() {
        SceneObject& obj = emplace_in_map(m_objs);
        m_nodes[obj.get_id()].parent = 0;
        return obj;
    }

    // remove
    void SceneContainer::remove_scene_obj(const SceneObject& obj) {
        m_nodes.at(m_nodes.at(obj.get_id()).parent).childs.erase(obj.get_id());
        m_nodes.erase(obj.get_id());
        m_objs.erase(obj.get_id());
    }

    // parent
    void SceneContainer::set_parent(const SceneObject& obj, const SceneObject& parent) {
        const ID parent_id = m_nodes.at(obj.get_id()).parent;
        if (parent_id != 0) {
            m_nodes.at(parent_id).childs.erase(obj.get_id());
        }
        m_nodes.at(obj.get_id()).parent = parent.get_id();
        m_nodes.at(parent.get_id()).childs.insert(obj.get_id());
    }
    SceneObject& SceneContainer::get_parent(const SceneObject& obj) {
        return m_objs.at(m_nodes.at(obj.get_id()).parent);
    }
    const SceneObject& SceneContainer::get_parent(const SceneObject& obj) const {
        return m_objs.at(m_nodes.at(obj.get_id()).parent);
    }

    // access
    SceneObject& SceneContainer::get_scene_obj(const string& name) {
        for (auto& [id, obj] : m_objs) {
            if (obj.name == name) {
                return obj;
            }
        }
    }
    const SceneObject& SceneContainer::get_scene_obj(const string& name) const {
        for (const auto& [id, obj] : m_objs) {
            if (obj.name == name) {
                return obj;
            }
        }
    }
    Map<ID, SceneObject>& SceneContainer::get_scene_objs() {
        return m_objs;
    }
    const Map<ID, SceneObject>& SceneContainer::get_scene_objs() const {
        return m_objs;
    }
}