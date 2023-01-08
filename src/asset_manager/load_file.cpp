#include "load_file.hpp"
#include "file_loader/OBJ_loader/OBJ_loader.h"
#include "file_loader/lodepng/lodepng.h"
#include <iostream>

namespace intern {
    Mesh* load_obj(const Filepath& filepath) {
        objl::Loader loader;
        loader.LoadFile(filepath);

        Mesh* out = new Mesh();
        out->indices = loader.LoadedIndices;
        for (const auto& vertex : loader.LoadedVertices) {
            out->vertices.emplace_back(
                Vec3f(vertex.Position.X, vertex.Position.Y, vertex.Position.Z),
                Vec3f(vertex.Normal.X, vertex.Normal.Y, vertex.Normal.Z),
                Vec2f(vertex.TextureCoordinate.X, vertex.TextureCoordinate.Y));
        }
        // out.positions.reserve(loader.LoadedVertices.size());
        // out.normals.reserve(loader.LoadedVertices.size());
        // out.tex_coords.reserve(loader.LoadedVertices.size());
        // for (const auto& vertex : loader.LoadedVertices) {
        //     out.positions.emplace_back(vertex.Position.X, vertex.Position.Y, vertex.Position.Z);
        //     out.normals.emplace_back(vertex.Normal.X, vertex.Normal.Y, vertex.Normal.Z);
        //     out.tex_coords.emplace_back(vertex.TextureCoordinate.X, vertex.Position.Y);
        // }
        return out;
    }
    Image* load_png(const Filepath& filepath) {
        List<byte> bytes;
        unsigned width, height;

        //decode
        u32 error = lodepng::decode(bytes, width, height, filepath);

        //if there's an error, display it
        if(error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;

        List<RGBA> buffer;
        for (adress i = 0; i < bytes.size(); i += 4) {
            buffer.emplace_back(bytes[i + 0], bytes[i + 1], bytes[i + 2], bytes[i + 3]);
        }
        return new Image(std::move(buffer), Vec2u(width, height));
    }
}