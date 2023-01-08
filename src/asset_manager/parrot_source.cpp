#include "parrot_source.hpp"
#include "asset_manager.hpp"
#include "application/application.hpp"

namespace intern {
    static string remove_whitespace(const string& str) {
        adress begin = 0;
        while (begin < str.size() && (str[begin] == ' ' || str[begin] == '\t')) {
            ++begin;
        }
        adress end = str.size() - 1;
        while (end > 0 && (str[end] == ' ' || str[end] == '\t')) {
            --end;
        }
        if (end <= begin) {
            return "";
        }
        else {
            return str.substr(begin, end + 1);
        }
    }
    static f32 to_f32(std::string::const_iterator begin, std::string::const_iterator end) {
        return std::stof(string(begin, end));
    }
    static ParrotSourceValue create_source_val(const string& str) {
        // string
        if (str[0] == '\"') {
            return ParrotSourceValue(str.substr(1, str.size() - 2));
        }

        // list
        if (str.front() == '[' && str.back() == ']') {
            List<string> string_list;
            adress begin = 1;
            while (true) {
                adress comma = str.find(',', begin);
                string val;
                if (comma == str.npos) {
                    val = remove_whitespace(str.substr(begin, (str.size() - begin - 2)));
                }
                else {
                    val = remove_whitespace(str.substr(begin, (comma - begin)));
                }
                val = val.substr(1, val.size() - 2);
                string_list.push_back(std::move(val));

                if (comma == str.npos) {
                    break;
                }
                begin = comma + 1;
            }
            return ParrotSourceValue(string_list);
        }

        // number / vectors
        adress space1 = str.find(' ');
        if (space1 == str.npos) {
            return ParrotSourceValue(
                to_f32(str.begin(), str.end()
            ));
        }
        adress space2 = str.find(' ', space1 + 1);
        if (space2 == str.npos) {
            return ParrotSourceValue(Vec2f(
                to_f32(str.begin(), str.begin() + space1),
                to_f32(str.begin() + space1 + 1, str.end())
            ));
        }
        adress space3 = str.find(' ', space2 + 1);
        if (space3 == str.npos) {
            return ParrotSourceValue(Vec3f(
                to_f32(str.begin(), str.begin() + space1),
                to_f32(str.begin() + space1 + 1, str.begin() + space2),
                to_f32(str.begin() + space2 + 1, str.end())
            ));
        }
        return ParrotSourceValue(Vec4f(
            to_f32(str.begin(), str.begin() + space1),
            to_f32(str.begin() + space1 + 1, str.begin() + space2),
            to_f32(str.begin() + space2 + 1, str.begin() + space3),
            to_f32(str.begin() + space3 + 1, str.end())
        ));
    }

    List<ParrotSource> load_parrot_source(const Filepath& filepath) {
        File file(filepath);

        List<ParrotSource> src;
        Stack<ParrotSourceNode*> nodes;
        while (!file.reached_end()) {
            string line = remove_whitespace(file.read_line());

            // comment
            if (line.empty() || line.front() == '#') {
                continue;
            }

            if (line.back() == ':') {
                // start source
                if (line.starts_with("window ")) {
                    src.emplace_back(ParrotSourceType::Window, line.substr(7, line.size() - 8));
                    nodes.push(&src.back().root);
                }
                else if (line.starts_with("scene ")) {
                    src.emplace_back(ParrotSourceType::Scene, line.substr(6, line.size() - 7));
                    nodes.push(&src.back().root);
                }
                else if (line.starts_with("scene_object ")) {
                    src.emplace_back(ParrotSourceType::SceneObject, line.substr(13, line.size() - 14));
                    nodes.push(&src.back().root);
                }
                else if (line.starts_with("material ")) {
                    src.emplace_back(ParrotSourceType::Material, line.substr(9, line.size() - 10));
                    nodes.push(&src.back().root);
                }
                // start node
                else {
                    string name = line.substr(0, line.size() - 1);
                    nodes.top()->childs.insert_or_assign(name, new ParrotSourceNode(name));
                    nodes.push(nodes.top()->childs.at(name));
                }
            }
            else if (line == "END") {
                nodes.pop();
            }
            else {
                string name = line.substr(0, line.find(' '));
                nodes.top()->values.insert_or_assign(name, create_source_val(line.substr(name.size() + 1)));
            }
        }
        return src;
    }

    static void set_material_val(const string& name, const ParrotSourceValue& val, Material& material) {
        switch (val.dtype) {
        case ParrotSourceDataType::String:
            if (std::get<string>(val.data).ends_with(".png")) {
                material.set_texture(name, AssetManager::get_image(std::get<string>(val.data)));
            }
            break;
        case ParrotSourceDataType::Number:
            material.set_f32(name, std::get<f32>(val.data));
            break;
        case ParrotSourceDataType::Vec2:
            material.set_vec2f(name, std::get<Vec2f>(val.data));
            break;
        case ParrotSourceDataType::Vec3:
            material.set_vec3f(name, std::get<Vec3f>(val.data));
            break;
        case ParrotSourceDataType::Vec4:
            material.set_vec4f(name, std::get<Vec4f>(val.data));
            break;
        default:
            return;
        }
    }
    static void recursive_set_material_values(const ParrotSourceNode& node, Material& material) {
        for (const auto& [name, val] : node.values) {
            set_material_val(name, val, material);
        }
        for (const auto& [name, child] : node.childs) {
            recursive_set_material_values(*child, material);
        }
    }
    Material* create_material_from_src(const ParrotSource& src) {
        Material* material = new Material(AssetManager::get_shader(
            std::get<string>(src.root.values.at("vertex").data),
            std::get<string>(src.root.values.at("fragment").data))
        );
        recursive_set_material_values(src.root, *material);
        return material;
    }
}