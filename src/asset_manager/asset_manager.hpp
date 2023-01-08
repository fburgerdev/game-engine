#pragma once
#include "utils/file.hpp"
#include "renderer/image.hpp"
#include "renderer/mesh.hpp"
#include "renderer/material.hpp"
#include "parrot_source.hpp"

namespace intern {
    class AssetManager {
    public:
        static Mesh& get_mesh(const Filename& filename);
        static Image& get_image(const Filename& filename);
        static Shader& get_shader(const Filename& vertex, const Filename& fragment);
        static Material& get_material(const Filename& filename);
        static List<ParrotSource>& get_parrot_src(const Filename& filename);

        static Image& get_flat_image();
        static Shader& get_model_shader();
        static Material& get_flat_material();

        static void set_root(const string& root);
    private:
        static inline string s_root;
        static inline Map<Filename, Mesh*> s_meshes;
        static inline Map<Filename, Image*> s_images;
        static inline Map<Filename, Shader*> s_shaders;
        static inline Map<Filename, Material*> s_materials;
        static inline Map<Filename, List<ParrotSource>> s_parrot_src;
    };
}