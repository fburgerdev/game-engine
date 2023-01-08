#pragma once
#include "scene_api.hpp"
#include "utils/file.hpp"
#include "renderer/image.hpp"

namespace intern {
    Mesh* load_obj(const Filepath& filepath);
    Image* load_png(const Filepath& filepath);
}