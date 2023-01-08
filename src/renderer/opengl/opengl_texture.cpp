#include "opengl_texture.hpp"
#include <GL/glew.h>

namespace intern {
    Texture_OPENGL::Texture_OPENGL(const RGBA* buffer, Vec2u size, const TexConfig& config)
        : m_id(0) {
        glGenTextures(1, &m_id);
        glBindTexture(GL_TEXTURE_2D, m_id);
        glEnable(GL_TEXTURE_2D);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void*)buffer);
        if (config.mipmap != TexConfig::Mipmap::None)
            glGenerateMipmap(GL_TEXTURE_2D);

        i32 minFilter;
        if (config.mipmap == TexConfig::Mipmap::None)
            minFilter = (i32)config.minFilter;
        else if (config.minFilter == TexConfig::Filter::Linear && config.mipmap == TexConfig::Mipmap::Linear)
            minFilter = GL_LINEAR_MIPMAP_LINEAR;
        else if (config.minFilter == TexConfig::Filter::Linear && config.mipmap == TexConfig::Mipmap::Nearest)
            minFilter = GL_LINEAR_MIPMAP_NEAREST;
        else if (config.minFilter == TexConfig::Filter::Nearest && config.mipmap == TexConfig::Mipmap::Linear)
            minFilter = GL_NEAREST_MIPMAP_LINEAR;
        else
            minFilter = GL_NEAREST_MIPMAP_NEAREST;

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (i32)config.magFilter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (i32)config.horWrap);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (i32)config.verWrap);
    }
    Texture_OPENGL::~Texture_OPENGL() {
        glDeleteTextures(1, &m_id);
    }

    void Texture_OPENGL::bind(u32 slot) const {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_id);
    }
    void Texture_OPENGL::unbind() const {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}