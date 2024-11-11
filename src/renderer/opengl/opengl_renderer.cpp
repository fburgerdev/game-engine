#include "opengl_renderer.hpp"
#include "opengl_shader.hpp"
#include "opengl_buffer.hpp"
#include "opengl_texture.hpp"
#include "asset_manager_api.hpp"
#include "utils/file.hpp"
#include "scene_api.hpp"
#include "renderer/projection.hpp"
#include <glad/glad.h>

namespace intern {
    // static Image s_image;
    // static Texture_OPENGL* s_tex;
    
    Renderer_OPENGL::Renderer_OPENGL(const Window& window)
        : Renderer(window) {
        // for (const Scene& scene : window.get_scenes()) {
        //     for (const auto& [id, scene_obj] : scene.get_scene_objs()) {
        //         if (scene_obj.has_component(ComponentType::RenderObject)) {
        //             const RenderObject& render_obj = scene_obj.get_render_object();
        //             if (!m_vertex_buffers.contains(render_obj.mesh.get_id())) {
        //                 m_vertex_buffers[render_obj.mesh.get_id()] = VertexBuffer_OPENGL((const void*)render_obj.mesh.vertices.data(), render_obj.mesh.vertices.size(), true);
        //             }
        //             if (!m_shaders.contains(render_obj.material.shader.get_id())) {
        //                 m_shaders[render_obj.material.shader.get_id()] = Shader_OPENGL(render_obj.material.shader.vertex, render_obj.material.shader.fragment);
        //             }
        //         }
        //     }
        // }
        // s_image = load_image("../assets/textures/parrot.png");
        // s_tex = new Texture_OPENGL(s_image.data(), s_image.get_size());
        // s_tex->bind(1);
    }

    void Renderer_OPENGL::bind_material(const Material& material) {
        Shader_OPENGL& shader = *m_shaders.at(material.shader.get_id());
        shader.bind();
        for (const auto&[name, val] : material.get_i32_map()) {
            shader.set_uniform_i32(name, val);
        }
        for (const auto&[name, val] : material.get_vec2i_map()) {
            shader.set_uniform_vec2i(name, val);
        }
        for (const auto&[name, val] : material.get_vec3i_map()) {
            shader.set_uniform_vec3i(name, val);
        }
        for (const auto&[name, val] : material.get_vec4i_map()) {
            shader.set_uniform_vec4i(name, val);
        }
        
        for (const auto&[name, val] : material.get_f32_map()) {
            shader.set_uniform_f32(name, val);
        }
        for (const auto&[name, val] : material.get_vec2f_map()) {
            shader.set_uniform_vec2f(name, val);
        }
        for (const auto&[name, val] : material.get_vec3f_map()) {
            shader.set_uniform_vec3f(name, val);
        }
        for (const auto&[name, val] : material.get_vec4f_map()) {
            shader.set_uniform_vec4f(name, val);
        }

        for (const auto&[name, val] : material.get_mat2f_map()) {
            shader.set_uniform_mat2f(name, val);
        }
        for (const auto&[name, val] : material.get_mat3f_map()) {
            shader.set_uniform_mat3f(name, val);
        }
        for (const auto&[name, val] : material.get_mat4f_map()) {
            // debug.log(val);
            shader.set_uniform_mat4f(name, val);
        }

        i32 slot = 1;
        for (const auto&[name, texture] : material.get_texture_map()) {
            Texture_OPENGL& tex_opengl = *m_textures.at(texture->get_id());
            tex_opengl.bind(slot);
            shader.set_uniform_i32(name, slot);
            slot++;
        }
    }

    void Renderer_OPENGL::clear() {
        glEnable(GL_DEPTH_TEST);
   		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
    }
    void Renderer_OPENGL::render_scene_obj(const Scene& scene, const SceneObject& scene_obj) {
        const RenderObject& render_obj = scene_obj.get_render_object();
        
        // material
        render_obj.material.prepare_scene_obj_draw(scene, scene_obj);
        bind_material(render_obj.material);
        
        // buffer
        VertexBuffer_OPENGL& vb = *m_vertex_buffers.at(render_obj.mesh.get_id());
        
        VertexBufferLayout layout;
        layout.push(VertexBufferElement::DType::F32, 3);
        layout.push(VertexBufferElement::DType::F32, 3);
        layout.push(VertexBufferElement::DType::F32, 2);
        VertexArray_OPENGL va(vb, layout);
        va.bind();

        m_index_buffers.at(render_obj.mesh.get_id())->bind();
        
        // draw
        glDrawElements(GL_TRIANGLES, render_obj.mesh.indices.size(), GL_UNSIGNED_INT, NULL);
        // glDrawArrays(GL_TRIANGLES, 0, render_obj.mesh.vertices.size());
    }
    void Renderer_OPENGL::render_scene(const Scene& scene) {
        for (const auto& [id, scene_obj] : scene.get_scene_objs()) {
            if (scene_obj.has_component(ComponentType::RenderObject)) {
                const RenderObject& render_obj = scene_obj.get_render_object();
                if (!m_vertex_buffers.contains(render_obj.mesh.get_id())) {
                    m_vertex_buffers[render_obj.mesh.get_id()] = new VertexBuffer_OPENGL((const void*)render_obj.mesh.vertices.data(), render_obj.mesh.vertices.size() * sizeof(Vertex3D), false);
                }
                if (!m_index_buffers.contains(render_obj.mesh.get_id())) {
                    m_index_buffers[render_obj.mesh.get_id()] = new IndexBuffer_OPENGL(render_obj.mesh.indices, false);
                }
                if (!m_shaders.contains(render_obj.material.shader.get_id())) {
                    m_shaders[render_obj.material.shader.get_id()] = new Shader_OPENGL(render_obj.material.shader.vertex, render_obj.material.shader.fragment);
                }
                for (const auto& [name, texture] : render_obj.material.get_texture_map()) {
                    if (!m_textures.contains(texture->get_id())) {
                        m_textures[texture->get_id()] = new Texture_OPENGL(texture->data(), texture->get_size());
                    }
                }
            }
        }

        for (const auto&[id, scene_obj] : scene.get_scene_objs()) {
            if (scene_obj.has_component(ComponentType::RenderObject)) {
                render_scene_obj(scene, scene_obj);
            }
        }
    }
}