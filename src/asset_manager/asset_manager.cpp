#include "asset_manager.hpp"
#include "load_file.hpp"
#include "renderer_api.hpp"
#include "parrot_source.hpp"

namespace intern {
    Mesh& AssetManager::get_mesh(const Filepath& filename) {
        if (!s_meshes.contains(filename)) {
            s_meshes.insert({ filename, load_obj(find_in_directory(filename, s_root)) });
        }
        return *s_meshes.at(filename);
    }
    Image& AssetManager::get_image(const Filepath& filename) {
        if (!s_meshes.contains(filename)) {
            s_images.insert({ filename, load_png(find_in_directory(filename, s_root)) });
        }
        return *s_images.at(filename);
    }
    Shader& AssetManager::get_shader(const Filepath& vertex, const Filepath& fragment) {
        const string key = vertex + fragment;
        if (!s_shaders.contains(key)) {
            s_shaders.insert({ key, new Shader(
                File(find_in_directory(vertex, s_root)).extract_all(),
                File(find_in_directory(fragment, s_root)).extract_all()
            ) });
        }
        return *s_shaders.at(key);
    }
    Material& AssetManager::get_material(const Filepath& filename) {
        if (!s_materials.contains(filename)) {
            s_materials.insert({ filename, create_material_from_src(get_parrot_src(filename).front()) });
        }
        return *s_materials.at(filename);
    }
    List<ParrotSource>& AssetManager::get_parrot_src(const Filename& filename) {
        if (!s_parrot_src.contains(filename)) {
            s_parrot_src.insert({ filename, std::move(load_parrot_source(find_in_directory(filename, s_root))) });
        }
        return s_parrot_src.at(filename);
    }

    Image& AssetManager::get_flat_image() {
        return get_image("flat.png");
    }
    Shader& AssetManager::get_model_shader() {
        return get_shader("model.vs", "model.fs");
    }
    Material& AssetManager::get_flat_material() {
        return get_material("flat.mat");
    }

    void AssetManager::set_root(const string& root) {
        s_root = root;
    }
}