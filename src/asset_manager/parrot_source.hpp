#pragma once
#include "math_api.hpp"
#include "renderer/material.hpp"
#include "utils/file.hpp"
#include <variant>

namespace intern {
    enum class ParrotSourceType {
        Window, Scene, SceneObject, Material
    };
    enum class ParrotSourceDataType {
        None, String, Number, Vec2, Vec3, Vec4, StringList
    };
    struct ParrotSourceValue {
        ParrotSourceValue()
            : dtype(ParrotSourceDataType::None), data() {}
        ParrotSourceValue(const string& str)
            : dtype(ParrotSourceDataType::String), data(str) {}
        ParrotSourceValue(f32 number)
            : dtype(ParrotSourceDataType::Number), data(number) {}
        ParrotSourceValue(const Vec2f& vec2)
            : dtype(ParrotSourceDataType::Vec2), data(vec2) {}
        ParrotSourceValue(const Vec3f& vec3)
            : dtype(ParrotSourceDataType::Vec3), data(vec3) {}
        ParrotSourceValue(const Vec4f& vec4)
            : dtype(ParrotSourceDataType::Vec4), data(vec4) {}
        ParrotSourceValue(const List<string>& list)
            : dtype(ParrotSourceDataType::StringList), data(list) {}

        ParrotSourceDataType dtype;
        std::variant<string, f32, Vec2f, Vec3f, Vec4f, List<string>> data;
    };
    struct ParrotSourceNode {
        ParrotSourceNode() = default;
        ParrotSourceNode(const string& name)
            : name(name) {}

        string name;
        Map<string, ParrotSourceValue> values;
        Map<string, ParrotSourceNode*> childs;
    };
    struct ParrotSource {
        ParrotSource(ParrotSourceType type, const string& name)
            : type(type), root(name) {}

        ParrotSourceType type;
        ParrotSourceNode root;
    };

    List<ParrotSource> load_parrot_source(const Filepath& filepath);
    Material* create_material_from_src(const ParrotSource& src);
}