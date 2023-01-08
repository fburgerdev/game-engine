#pragma once
#include "component.hpp"
#include "renderer/mesh.hpp"
#include "renderer/material.hpp"

namespace intern {
    struct RenderObject : public Component {
        RenderObject(Mesh& mesh, Material& material)
            : Component(ComponentType::RenderObject), mesh(mesh), material(material) {}

        Mesh& mesh;
        Material& material;
    };
}