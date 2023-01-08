#pragma once
#include "math_api.hpp"

namespace intern {
    class Shader_OPENGL {
    public:
        Shader_OPENGL() = default;
        Shader_OPENGL(const string& vertex_src, const string& fragment_src, const string& geometry_src = "");
        Shader_OPENGL(Shader_OPENGL&& other);
        ~Shader_OPENGL();

        void bind() const;
        void unbind() const;

        void set_uniform_i32(const string& identifier, i32 val) const;
        void set_uniform_vec2i(const string& identifier, const Vec2i& val) const;
        void set_uniform_vec3i(const string& identifier, const Vec3i& val) const;
        void set_uniform_vec4i(const string& identifier, const Vec4i& val) const;

        void set_uniform_f32(const string& identifier, f32 val) const;
        void set_uniform_vec2f(const string& identifier, const Vec2f& val) const;
        void set_uniform_vec3f(const string& identifier, const Vec3f& val) const;
        void set_uniform_vec4f(const string& identifier, const Vec4f& val) const;

        void set_uniform_mat2f(const string& identifier, const Mat2f& mat) const;
        void set_uniform_mat3f(const string& identifier, const Mat3f& mat) const;
        void set_uniform_mat4f(const string& identifier, const Mat4f& mat) const;
    private:
        u32 compile_shader(i32 shader_type, const string& src);
        u32 get_uniform_location(const string& identifier) const;
    private:
        u32 m_id;
        mutable Map<string, i32> m_uniform_location_cache;
    };
}