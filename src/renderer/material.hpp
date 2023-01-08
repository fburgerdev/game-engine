#pragma once
#include "shader.hpp"
#include "math_api.hpp"
#include "image.hpp"
#include <functional>

namespace intern {
    struct Scene;
    struct SceneObject;
    class Material {
    public:
        Material(Shader& shader);

        void set_scene_draw_prepare(std::function<void(const Scene&, Material&)> callback);
        void set_scene_obj_draw_prepare(std::function<void(const Scene&, const SceneObject&, Material&)> callback);

        void prepare_scene_draw(const Scene& scene);
        void prepare_scene_obj_draw(const Scene&, const SceneObject& scene_obj);

        void set_i32(const string& name, i32 val);
        void set_vec2i(const string& name, const Vec2i& val);
        void set_vec3i(const string& name, const Vec3i& val);
        void set_vec4i(const string& name, const Vec4i& val);

        void set_f32(const string& name, f32 val);
        void set_vec2f(const string& name, const Vec2f& val);
        void set_vec3f(const string& name, const Vec3f& val);
        void set_vec4f(const string& name, const Vec4f& val);

        void set_mat2f(const string& name, const Mat2f& val);
        void set_mat3f(const string& name, const Mat3f& val);
        void set_mat4f(const string& name, const Mat4f& val);

        void set_texture(const string& name, const Image& texture);

        const Map<string, i32>& get_i32_map() const;
        const Map<string, Vec2i>& get_vec2i_map() const;
        const Map<string, Vec3i>& get_vec3i_map() const;
        const Map<string, Vec4i>& get_vec4i_map() const;
 
        const Map<string, f32>& get_f32_map() const;
        const Map<string, Vec2f>& get_vec2f_map() const;
        const Map<string, Vec3f>& get_vec3f_map() const;
        const Map<string, Vec4f>& get_vec4f_map() const;

        const Map<string, Mat2f>& get_mat2f_map() const;
        const Map<string, Mat3f>& get_mat3f_map() const;
        const Map<string, Mat4f>& get_mat4f_map() const;
        
        const Map<string, const Image*>& get_texture_map() const;

        Shader& shader;
    private:
        std::function<void(const Scene&, Material&)> m_scene_draw_prepare;
        std::function<void(const Scene&, const SceneObject&, Material&)> m_scene_obj_draw_prepare;

        Map<string, i32> m_uniforms_i32;
        Map<string, Vec2i> m_uniforms_vec2i;
        Map<string, Vec3i> m_uniforms_vec3i;
        Map<string, Vec4i> m_uniforms_vec4i;

        Map<string, f32> m_uniforms_f32;
        Map<string, Vec2f> m_uniforms_vec2f;
        Map<string, Vec3f> m_uniforms_vec3f;
        Map<string, Vec4f> m_uniforms_vec4f;

        Map<string, Mat2f> m_uniforms_mat2f;
        Map<string, Mat3f> m_uniforms_mat3f;
        Map<string, Mat4f> m_uniforms_mat4f;

        Map<string, const Image*> m_uniforms_texture;
    };
}