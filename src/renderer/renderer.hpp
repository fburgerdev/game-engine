#pragma once
#include "window_api.hpp"

namespace intern {
    class Renderer {
    public:
        Renderer(const Window& window)
            : m_window(window) {}

        virtual void clear() = 0;
        virtual void render_scene(const Scene& scene) = 0;
        void render_all();
    protected:
        const Window& m_window;
    };

    Renderer& create_renderer(Window& window);
}