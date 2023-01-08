#include "image.hpp"

namespace intern
{
    Image::Image(const List<RGBA>& buffer, Vec2u size) 
        : ObjID(), m_buffer(buffer), m_size(size) {}
    Image::Image(List<RGBA>&& buffer, Vec2u size)
        : ObjID(), m_buffer(std::move(buffer)), m_size(size) {}
    Vec2u Image::get_size() const {
        return m_size;
    }
    bool Image::in_bounds(u32 x, u32 y) const {
        return x < m_size.x && y < m_size.y;
    }
    RGBA& Image::at(u32 x, u32 y) {
        return m_buffer[m_size.x * y + x];
    }
    const RGBA& Image::at(u32 x, u32 y) const {
        return m_buffer[m_size.x * y + x];
    }
    RGBA* Image::data() {
        return m_buffer.data();
    }
    const RGBA* Image::data() const {
        return m_buffer.data();
    }
}
