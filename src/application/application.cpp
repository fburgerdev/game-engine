#include "application.hpp"
#include "renderer_api.hpp"
#include "utils/time.hpp"
#include "debug_api.hpp"
#include "utils/file.hpp"
#include "utils/async.hpp"
#include "event_api.hpp"
#include "config.hpp"
#include "asset_manager_api.hpp"
#include <thread>

namespace intern {
    static void poll_events(Window* window) {
        while (window->has_events()) {
            Event e = window->pop_event();

            // close window
            if (e.type == EventType::WindowCloseRequest) {
                window->close();
            }
            // if (e.type == EventType::KeyPress) {
            //     if (e.key_press.code == KeyCode::KEY_ESCAPE) {
            //         window->close();
            //     }
            // }

            // on event
            for (Scene& scene : window->get_scenes()) {
                for (auto& [id, obj] : scene.get_scene_objs()) {
                    for (auto& [hash, script] : obj.get_scripts()) {
                        script->on_event(e);
                    }
                }
            }
        }
    }
    static void on_update(Window* window, Timestep ts) {
        for (Scene& scene : window->get_scenes()) {
            for (auto& [id, obj] : scene.get_scene_objs()) {
                for (auto& [hash, script] : obj.get_scripts()) {
                    script->on_update(ts);
                }
            }
        }
    }
    
    Window& Application::create_window_from_src(const ParrotSource& src) {
        string title = "Unnamed";
        if (src.root.values.contains("title")) {
            title = std::get<string>(src.root.values.at("title").data);
        }
        Vec2u size = Vec2u(1080, 720);
        if (src.root.values.contains("size")) {
            size = Vec2u(std::get<Vec2f>(src.root.values.at("size").data));    
        }
        Window& window = create_window(title, size);

        s_active_window = &window;
        if (src.root.values.contains("scenes")) {
            for (const string& scene : std::get<List<string>>(src.root.values.at("scenes").data)) {
                window.push_scene_from_src(AssetManager::get_parrot_src(scene).front());
            }
        }
        s_active_window = &window;
        return window;
    }

    void init(); // defined in launch.cpp
    void Application::launch() {
        init();
        debug.info("==== parrot launched ====", 
            "\n\tversion:", to_string(PT_VERSION_MAJOR) + "." + to_string(PT_VERSION_MINOR),
            "\n\tconfig:", (PT_CONFIG == PT_DEBUG ? "debug" : (PT_CONFIG == PT_OPTIMIZED ? "optimized" : (PT_CONFIG == PT_DIST ? "dist" : "unknown"))),
            "\n\tplatform:", (PT_PLATFORM == PT_LINUX ? "linux" : (PT_PLATFORM == PT_WINDOWS ? "windows" : "unknown")),
            "\n\trender_api:", (PT_RENDER_API == PT_OPENGL ? "opengl" : "unknown"),
            "\n\twindow_api:", (PT_WINDOW_API == PT_GLFW ? "glfw" : "unknown")
        );
        
        // on_create();
        Stopwatch frame_watch;
        Timestep frame_time;
        while (s_windows.size() > 0) {
            frame_time = frame_watch.time();
            frame_watch.reset();
            for (auto& pair : s_windows) {
                s_active_window = pair.second;
                Window& window = *pair.second;
                if (window.is_open()) {
                    // render
                    window.bind();
                    s_renderers.at(window.get_id())->render_all();
                    window.update();

                    on_update(&window, frame_time);
                    poll_events(&window);
                    // std::thread(on_update, &window, frame_time).detach();
                    // std::thread(poll_events, &window).detach();
                }
            }
            update_window_map();
        }

        debug.info("==== parrot terminated ====", 
            "\n\texit status:", "success", 
            "\n\tduration:", s_watch.time()
        );
    }
    void Application::terminate() {
        for (auto&[id, window] : s_windows) {
            window->close();
        }
    }
    Timestep Application::time() {
        return s_watch.time();
    }
    Window& Application::current_window() {
        return *s_active_window;
    }
    Window& Application::get_window(const string& title) {
        for (auto& [id, window] : s_windows) {
            if (window->title == title) {
                return *window;
            }
        }
    }
    void Application::update_window_map() {
        if (s_windows.size() == 0) {
            return;
        }
        for (auto& [id, window] : s_windows) {
            if (!window->is_open()) {
                delete s_windows.at(id);
                s_windows.erase(id);
                return update_window_map();
            }
        }
    }
}