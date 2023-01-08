#include "application_api.hpp"
#include "asset_manager_api.hpp"
#include "asset_manager/parrot_source.hpp"
#include "debug_api.hpp"
#include "editor/scripts/cube.hpp"
#include "editor/scripts/player_controller.hpp"

namespace intern {
    std::pair<adress, Script*> create_script_from_string(const string& name, SceneObject& scene_obj) {
        if (name == "Cube") {
            return { typeid(Cube).hash_code(), new Cube(scene_obj) };
        }
        else if (name == "PlayerController") {
            return { typeid(PlayerController).hash_code(), new PlayerController(scene_obj) };
        }
    }

    void init() {
        AssetManager::set_root("../assets/");
        Application::create_window_from_src(AssetManager::get_parrot_src("main.wndw").front());
    }
}