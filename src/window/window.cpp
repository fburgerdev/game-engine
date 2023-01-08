#include "application/application.hpp"
#include "glfw_window.hpp"
#include "debug_api.hpp"
#include "asset_manager_api.hpp"

namespace intern {
    Window::Window(const string& title)
        : ObjID(), title(title), m_scenes(), m_close(false) {}
    void Window::close() {
        m_close = true;
    }
    bool Window::is_open() const {
        return !m_close;
    }
    List<Scene>& Window::get_scenes() {
        return m_scenes;
    }
    Scene& Window::get_scene(const string& name) {
        for (Scene& scene : m_scenes) {
            if (scene.name == name) {
                return scene;
            }
        }
    }
    const List<Scene>& Window::get_scenes() const {
        return m_scenes;
    }
    Scene& Window::push_scene() {
        m_scenes.emplace_back();
        return m_scenes.back();
    }
    Scene& Window::push_scene_from_src(const ParrotSource& src) {
        Scene& scene = m_scenes.emplace_back(src.root.name);
        if (src.root.childs.contains("scene_objects")) {
            const ParrotSourceNode* scene_objects_node = src.root.childs.at("scene_objects");
            for (const auto&[name, node] : scene_objects_node->childs) {
                SceneObject& scene_obj = scene.create_scene_obj(name);

                // transform
                if (node->childs.contains("transform")) {
                    const ParrotSourceNode* transform_node = node->childs.at("transform");
                    if (transform_node->values.contains("pos")) {
                        scene_obj.transform.pos = std::get<Vec3f>(transform_node->values.at("pos").data);
                    }
                    if (transform_node->values.contains("rot")) {
                        scene_obj.transform.rot = std::get<Vec3f>(transform_node->values.at("rot").data);
                    }
                    if (transform_node->values.contains("scale")) {
                        scene_obj.transform.scale = std::get<Vec3f>(transform_node->values.at("scale").data);
                    }
                }

                // render_object
                if (node->childs.contains("camera")) {
                    const ParrotSourceNode* camera_node = node->childs.at("camera");
                    
                    if (camera_node->values.contains("projection")) {
                        string projection = std::get<string>(camera_node->values.at("projection").data);
                        if (projection == "Perspective") {
                            scene_obj.attach_camera(create_perspective_camera());
                        }
                        else if (projection == "Orthographic") {
                            scene_obj.attach_camera(create_orthographic_camera());
                        }
                    }
                    else {
                        scene_obj.attach_camera(create_perspective_camera());
                    }
                }

                // render_object
                if (node->childs.contains("render_object")) {
                    const ParrotSourceNode* render_obj_node = node->childs.at("render_object");
                    Mesh& mesh = AssetManager::get_mesh(std::get<string>(render_obj_node->values.at("mesh").data));
                    Material* material;
                    if (render_obj_node->values.contains("material")) {
                        material = &AssetManager::get_material(std::get<string>(render_obj_node->values.at("material").data));
                    }
                    else {
                        material = &AssetManager::get_flat_material();
                    }
                    scene_obj.attach_render_object(mesh, *material);
                }

                // scripts
                if (node->values.contains("scripts")) {
                    for (const string& script : std::get<List<string>>(node->values.at("scripts").data)) {
                        scene_obj.attach_script(script);
                    }
                }
            }
        }
        scene.set_main_camera(scene.get_scene_obj(std::get<string>(src.root.values.at("main_camera").data)));
    }

    Event Window::pop_event() {
        Event e = m_events.front();
        m_events.pop();
        return e;
    }
    void Window::push_event(Event e) {
        m_events.push(e);
    }
    bool Window::has_events() const {
        return !m_events.empty();
    }

    Window& Application::create_window(const string& title, Vec2u size) {
#if PT_WINDOW_API == PT_GLFW
        Window* window = static_cast<Window*>(new Window_GLFW(title, size));
#endif
        s_windows[window->get_id()] = window;
        s_renderers[window->get_id()] = &create_renderer(*window);
        return *window;
    }
}