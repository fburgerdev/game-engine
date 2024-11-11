#pragma once
#include "scene_api.hpp"
#include "debug_api.hpp"
#include "application_api.hpp"

namespace intern {
    class PlayerController : public Script {
    public:
        PlayerController(SceneObject& scene_obj) 
            : Script(scene_obj), m_window(Application::current_window()) {
            lose_focus();
        }

        void focus() {
            m_window.set_cursor_mode(CursorMode::Disabled);
            // m_window.set_cursor_pos(m_window.get_size() / 2U);
            m_last_cursor_pos = m_window.get_cursor_pos();
            m_has_focus = true;
        }
        void lose_focus() {
            m_has_focus = false;
            m_window.set_cursor_mode(CursorMode::Normal);
        }

        virtual void on_update(Timestep ts) override {
            debug.log(m_has_focus);
            if (!m_has_focus) {
                return;
            }

            // mouse move
            Vec2i cursor_pos = m_window.get_cursor_pos();
            Vec2i cursor_diff = cursor_pos - m_last_cursor_pos;
            if (cursor_pos != m_last_cursor_pos) {
                debug.log(cursor_pos);
            }

            transform.rot.y += cursor_diff.x * mouse_sensitivity * ts.sec();
            transform.rot.x -= cursor_diff.y * mouse_sensitivity * ts.sec();

            if (transform.rot.x < -PI / 2) {
                transform.rot.x = -PI / 2;
            }
            if (PI / 2 < transform.rot.x) {
                transform.rot.x = PI / 2;
            }

            m_last_cursor_pos = cursor_pos;

            // key move
            Mat3f rot_mat = resize<f32, 3, 3>(rotation_matrix(transform.rot));
            Vec3f forward = rot_mat * Vec3f(0, 0, 1);
            Vec3f right = rot_mat * Vec3f(1, 0, 0);
            Vec3f up = rot_mat * Vec3f(0, 1, 0);

            if (is_key_pressed(KeyCode::KEY_W)) {
                transform.pos += forward * speed * ts.sec();
            }
            if (is_key_pressed(KeyCode::KEY_S)) {
                transform.pos -= forward * speed * ts.sec();
            }
            if (is_key_pressed(KeyCode::KEY_D)) {
                transform.pos += right * speed * ts.sec();
            }
            if (is_key_pressed(KeyCode::KEY_A)) {
                transform.pos -= right * speed * ts.sec();
            }
            if (is_key_pressed(KeyCode::KEY_SPACE)) {
                transform.pos += up * speed * ts.sec();
            }
            if (is_key_pressed(KeyCode::KEY_LEFT_CONTROL)) {
                transform.pos -= up * speed * ts.sec();
            }
        }
        virtual void on_event(Event e) override {
            if (e.type == EventType::MouseClick) {
                if (e.mouse_click.button == MouseButton::Left) {
                    if (!m_has_focus) {
                        focus();
                    }
                }
            }
            if (e.type == EventType::KeyPress) {
                if (e.key_press.code == KeyCode::KEY_ESCAPE && e.key_press.state == KeyState::Press) {
                    if (m_has_focus) {
                        lose_focus();
                    }
                    else {
                        Application::current_window().close();
                    }
                }
            }
        }

        f32 speed = 5.0f;
        f32 mouse_sensitivity = 0.1f;
    private:
        Window& m_window;
        bool m_has_focus = false;
        Vec2i m_last_cursor_pos;
    };
}