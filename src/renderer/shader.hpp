#pragma once
#include "core_api.hpp"

namespace intern {
    struct Shader : public ObjID {
        Shader()
            : ObjID() {}
        Shader(const string& vertex, const string& fragment)
            : ObjID(), vertex(vertex), fragment(fragment) {}

        string vertex;
        string fragment;
    };
}