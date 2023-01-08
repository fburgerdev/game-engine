#include "script.hpp"
#include "scene/scene_object.hpp"

namespace intern {
    Script::Script(SceneObject& scene_obj)
        : transform(scene_obj.transform), scene_obj(scene_obj) {}
}