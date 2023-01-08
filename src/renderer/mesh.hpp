#pragma once
#include "core_api.hpp"
#include "math_api.hpp"

namespace intern {
    struct Vertex3D {
        Vec3f pos;
        Vec3f normal;
        Vec2f tex_coords;
    };
    struct Mesh : public ObjID {
        Mesh()
            : ObjID() {}
        Mesh(const List<Vertex3D>& vertices)
            : ObjID(), vertices(vertices) {}

        List<u32> indices;
        List<Vec3f> positions;
        List<Vec3f> normals;
        List<Vec2f> tex_coords;
        List<Vertex3D> vertices;
    };
}