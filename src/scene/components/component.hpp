#pragma once
#include "common.hpp"

namespace intern {
    enum class ComponentType {
        Camera, Mesh, RenderObject
    };
    struct Component {
        Component(ComponentType component_type)
            : component_type(component_type) {}
        ComponentType component_type;
    };
}