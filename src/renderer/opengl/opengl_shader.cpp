#include "opengl_shader.hpp"
#include <GL/glew.h>
#include "debug_api.hpp"
namespace intern {
    Shader_OPENGL::Shader_OPENGL(const string& vertexSrc, const string& fragmentSrc, const string& geometrySrc)
        : m_id(0)
    {
        m_id = glCreateProgram();
        u32 vs = compile_shader(GL_VERTEX_SHADER, vertexSrc);
        u32 fs = compile_shader(GL_FRAGMENT_SHADER, fragmentSrc);
        u32 gs = 0;
        if (!geometrySrc.empty()) {
            gs = compile_shader(GL_GEOMETRY_SHADER, geometrySrc);
        }

        glAttachShader(m_id, vs);
        glAttachShader(m_id, fs);
        if (!geometrySrc.empty()) {
            glAttachShader(m_id, gs);
        }
        glLinkProgram(m_id);
        glValidateProgram(m_id);

        glDeleteShader(vs);
        glDeleteShader(fs);
        if (!geometrySrc.empty()) {
            glDeleteShader(gs);
        }
    }
    Shader_OPENGL::~Shader_OPENGL() {
        if (m_id != 0) {
            glDeleteProgram(m_id);
        }
    }
    Shader_OPENGL::Shader_OPENGL(Shader_OPENGL&& other)
        : m_id(other.m_id), m_uniform_location_cache(other.m_uniform_location_cache) {
        other.m_id = 0;
    }


    void Shader_OPENGL::bind() const
    {
        glUseProgram(m_id);
    }
    void Shader_OPENGL::unbind() const
    {
        glUseProgram(0);
    }

    void Shader_OPENGL::set_uniform_i32(const string& identifier, i32 val) const
    {
        glUniform1i(get_uniform_location(identifier), val);
    }
    void Shader_OPENGL::set_uniform_vec2i(const string& identifier, const Vec2i& val) const
    {
        glUniform2i(get_uniform_location(identifier), val.x, val.y);
    }
    void Shader_OPENGL::set_uniform_vec3i(const string& identifier, const Vec3i& val) const
    {
        glUniform3i(get_uniform_location(identifier), val.x, val.y, val.z);
    }
    void Shader_OPENGL::set_uniform_vec4i(const string& identifier, const Vec4i& val) const
    {
        glUniform4i(get_uniform_location(identifier), val.x, val.y, val.z, val.w);
    }

    void Shader_OPENGL::set_uniform_f32(const string& identifier, f32 val) const
    {
        glUniform1f(get_uniform_location(identifier), val);
    }
    void Shader_OPENGL::set_uniform_vec2f(const string& identifier, const Vec2f& val) const
    {
        glUniform2f(get_uniform_location(identifier), val.x, val.y);
    }
    void Shader_OPENGL::set_uniform_vec3f(const string& identifier, const Vec3f& val) const
    {
        glUniform3f(get_uniform_location(identifier), val.x, val.y, val.z);
    }
    void Shader_OPENGL::set_uniform_vec4f(const string& identifier, const Vec4f& val) const
    {
        glUniform4f(get_uniform_location(identifier), val.x, val.y, val.z, val.w);
    }
    void Shader_OPENGL::set_uniform_mat2f(const string& identifier, const Mat2f& mat) const
    {
        glUniformMatrix2fv(get_uniform_location(identifier), 1, GL_TRUE, mat.data());
    }
    void Shader_OPENGL::set_uniform_mat3f(const string& identifier, const Mat3f& mat) const
    {
        glUniformMatrix3fv(get_uniform_location(identifier), 1, GL_TRUE, mat.data());
    }
    void Shader_OPENGL::set_uniform_mat4f(const string& identifier, const Mat4f& mat) const
    {
        glUniformMatrix4fv(get_uniform_location(identifier), 1, GL_TRUE, mat.data());
    }

    u32 Shader_OPENGL::compile_shader(i32 shaderType, const string& src)
    {
        u32 id = glCreateShader(shaderType);
        const char* srcCStr = src.c_str();
        glShaderSource(id, 1, &srcCStr, nullptr);
        glCompileShader(id);
        i32 result;
        glGetShaderiv(id, GL_COMPILE_STATUS, &result);

        if (result == GL_FALSE)
        {
            // cout << "shader compilation failed\n" << src;
            // i32 length;
            // glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
            // char* message = new char[length];
            // glGetShaderInfoLog(id, length, &length, message);
            // glDeleteShader(id);
            // // DebugOut << Error::ShaderCompilationError << message << '\n';
            // // DebugOut << (shaderType == GL_VERTEX_SHADER ? "\nVertex" : (shaderType == GL_FRAGMENT_SHADER ? "\nFragment" : "\nGeometry")) << " shader:\n";
            
            // adress lineStart = 0;
            // adress lineNum = 1;
            // while (true)
            // {
            //     adress lineEnd = src.find('\n', lineStart);
            //     DebugOut << '(' << lineNum << ")\t";
            //     if (lineEnd == src.npos)
            //     {
            //         DebugOut << string_view(src.c_str() + lineStart, src.length() - lineStart);
            //         break;
            //     }
            
            //     DebugOut << string_view(src.c_str() + lineStart, lineEnd + 1 - lineStart);
            //     lineStart = lineEnd + 1;
            //     lineNum++;
            // }
            // // DebugOut << Debugstream::EndMsg;
            
            // delete[] message;
            // return 0;
        }
        return id;
    }
    u32 Shader_OPENGL::get_uniform_location(const string& identifier) const
    {
        if (m_uniform_location_cache.contains(identifier)) {
            return m_uniform_location_cache.at(identifier);
        }

        i32 location = glGetUniformLocation(m_id, identifier.c_str());
        m_uniform_location_cache.emplace(identifier, location);
        return location;
    }
}