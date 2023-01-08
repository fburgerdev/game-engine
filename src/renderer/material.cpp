#include "material.hpp"
#include "projection.hpp"

namespace intern {
    static void no_scene_draw_prepare(const Scene& scene, Material& material) {}
    static void no_scene_obj_draw_prepare(const Scene& scene, const SceneObject& scene_obj, Material& material) {}

    Material::Material(Shader& shader)
        : shader(shader), m_scene_draw_prepare(no_scene_draw_prepare), m_scene_obj_draw_prepare(projection3D_scene_obj_draw_prepare) {}
    void Material::set_scene_draw_prepare(std::function<void(const Scene&, Material&)> callback) {
        m_scene_draw_prepare = callback;
    }
    void Material::set_scene_obj_draw_prepare(std::function<void(const Scene&, const SceneObject&, Material&)> callback) {
        m_scene_obj_draw_prepare = callback;
    }

    void Material::prepare_scene_draw(const Scene& scene) {
        m_scene_draw_prepare(scene, *this);
    }
    void Material::prepare_scene_obj_draw(const Scene& scene, const SceneObject& scene_obj) {
        m_scene_obj_draw_prepare(scene, scene_obj, *this);
    }

    void Material::set_i32(const string& name, i32 val) {
        m_uniforms_i32.insert_or_assign(name, val);
    }
    void Material::set_vec2i(const string& name, const Vec2i& val) {
        m_uniforms_vec2i.insert_or_assign(name, val);
    }
    void Material::set_vec3i(const string& name, const Vec3i& val) {
        m_uniforms_vec3i.insert_or_assign(name, val);
    }
    void Material::set_vec4i(const string& name, const Vec4i& val) {
        m_uniforms_vec4i.insert_or_assign(name, val);
    }

    void Material::set_f32(const string& name, f32 val) {
        m_uniforms_f32.insert_or_assign(name, val);
    }
    void Material::set_vec2f(const string& name, const Vec2f& val) {
        m_uniforms_vec2f.insert_or_assign(name, val);
    }
    void Material::set_vec3f(const string& name, const Vec3f& val) {
        m_uniforms_vec3f.insert_or_assign(name, val);
    }
    void Material::set_vec4f(const string& name, const Vec4f& val) {
        m_uniforms_vec4f.insert_or_assign(name, val);
    }

    void Material::set_mat2f(const string& name, const Mat2f& val) {
        m_uniforms_mat2f.insert_or_assign(name, val);
    }
    void Material::set_mat3f(const string& name, const Mat3f& val) {
        m_uniforms_mat3f.insert_or_assign(name, val);
    }
    void Material::set_mat4f(const string& name, const Mat4f& val) {
        m_uniforms_mat4f.insert_or_assign(name, val);
    }

    void Material::set_texture(const string& name, const Image& texture) {
        m_uniforms_texture.insert_or_assign(name, &texture);
    }

    const Map<string, i32>& Material::get_i32_map() const {
		return m_uniforms_i32;
	}
    const Map<string, Vec2i>& Material::get_vec2i_map() const {
		return m_uniforms_vec2i;
	}
    const Map<string, Vec3i>& Material::get_vec3i_map() const {
		return m_uniforms_vec3i;
	}
    const Map<string, Vec4i>& Material::get_vec4i_map() const {
		return m_uniforms_vec4i;
	}

    const Map<string, f32>& Material::get_f32_map() const {
		return m_uniforms_f32;
	}
    const Map<string, Vec2f>& Material::get_vec2f_map() const {
		return m_uniforms_vec2f;
	}
    const Map<string, Vec3f>& Material::get_vec3f_map() const {
		return m_uniforms_vec3f;
	}
    const Map<string, Vec4f>& Material::get_vec4f_map() const {
		return m_uniforms_vec4f;
	}

    const Map<string, Mat2f>& Material::get_mat2f_map() const {
        return m_uniforms_mat2f;
    }
    const Map<string, Mat3f>& Material::get_mat3f_map() const {
        return m_uniforms_mat3f;
    }
    const Map<string, Mat4f>& Material::get_mat4f_map() const {
        return m_uniforms_mat4f;
    }

    const Map<string, const Image*>& Material::get_texture_map() const {
        return m_uniforms_texture;
    }
}