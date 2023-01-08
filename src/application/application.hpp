#pragma once
#include "window_api.hpp"
#include "utils/time.hpp"
#include "renderer/renderer.hpp"
#include "asset_manager/parrot_source.hpp"

namespace intern {
    class Application {
    public:
        static Window& create_window(const string& title, Vec2u size);
        static Window& create_window_from_src(const ParrotSource& src);

        static void launch();
        static void terminate();

        static Timestep time();

        static Window& current_window();
        static Window& get_window(const string& title);
    private:
        static void update_window_map();
    private:
        static inline Window* s_active_window;
        static inline Map<ID, Window*> s_windows;
        static inline Map<ID, Renderer*> s_renderers;
        static inline Stopwatch s_watch;
    };
}