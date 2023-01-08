#include "opengl/opengl_renderer.hpp"

namespace intern {
    void Renderer::render_all() {
        clear();
        for (const Scene& scene : m_window.get_scenes()) {
            render_scene(scene);
        }
    }

    Renderer& create_renderer(Window& window) {
#if PT_GRAPHICS_API == PT_OPENGl
        return *static_cast<Renderer*>(new Renderer_OPENGL(window));
#endif
    }
}