#pragma once
#include "core_api.hpp"
#include "math_api.hpp"

namespace intern {
    struct RGBA {
        RGBA(u8 r, u8 g, u8 b, u8 a)
            : r(r), g(g), b(b), a(a) {}
        RGBA(u8 r, u8 g, u8 b)
            : r(r), g(g), b(b), a(255) {}
        RGBA(u8 brightness)
            : r(brightness), g(brightness), b(brightness), a(255) {}

        u8 r, g, b, a;
    };
    struct Image : public ObjID {
    public:
        Image()
            : ObjID() {}
        Image(const List<RGBA>& buffer, Vec2u size);
        Image(List<RGBA>&& buffer, Vec2u size);

        Vec2u get_size() const;
        bool in_bounds(u32 x, u32 y) const;
        
        RGBA& at(u32 x, u32 y);
        const RGBA& at(u32 x, u32 y) const;

        RGBA* data();
        const RGBA* data() const;
    private:
        List<RGBA> m_buffer;
        Vec2u m_size;
    };    
}