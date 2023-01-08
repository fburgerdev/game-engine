#pragma once
#include "math_api.hpp"
#include "renderer/image.hpp"

namespace intern {
    struct TexConfig {
        enum class Wrap : i32
        {
            ClampToEdge = 0x812F, ClampToBorder = 0x812D, Repeat = 0x2901, MirroredRepeat = 0x8370
        };
        enum class Filter : i32
        {
            Linear = 0x2601, Nearest = 0x2600
        };
        enum class Mipmap : uint8_t
        {
            None, Linear, Nearest
        };

        Wrap horWrap = Wrap::ClampToEdge;
        Wrap verWrap = Wrap::ClampToEdge;
        Filter magFilter = Filter::Linear;
        Filter minFilter = Filter::Linear;
        Mipmap mipmap = Mipmap::None;
    };
    class Texture_OPENGL {
    public:
        Texture_OPENGL(const RGBA* buffer, Vec2u size, const TexConfig& config = TexConfig());
        ~Texture_OPENGL();

        void bind(u32 slot) const;
        void unbind() const;
    private:
        u32 m_id;
    };
}