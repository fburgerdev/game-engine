#pragma once
#include "renderer_api.hpp"
#include "opengl_buffer.hpp"
#include "opengl_shader.hpp"
#include "opengl_texture.hpp"

namespace intern {
    class Renderer_OPENGL : public Renderer {
    public:
        Renderer_OPENGL(const Window& window);

        void bind_material(const Material& material);

        virtual void clear() override;
        void render_scene_obj(const Scene& scene, const SceneObject& scene_obj);
        virtual void render_scene(const Scene& scene) override;
    private:
        Map<ID, VertexBuffer_OPENGL*> m_vertex_buffers;
        Map<ID, IndexBuffer_OPENGL*> m_index_buffers;
        Map<ID, Shader_OPENGL*> m_shaders;
        Map<ID, Texture_OPENGL*> m_textures;
    };
}