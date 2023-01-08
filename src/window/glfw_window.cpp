#include "config.hpp"
#if PT_WINDOW_API == PT_GLFW
#include "glfw_window.hpp"
#include "debug_api.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <thread>

namespace intern {
    static Set<KeyCode> s_keys_pressed;
    bool is_key_pressed(KeyCode code) {
        return s_keys_pressed.contains(code);
    }

    static Map<GLFWwindow*, Window_GLFW*> s_handle_map;
    Window_GLFW::Window_GLFW(const string& title, Vec2u size) 
        : Window(title), m_handle(nullptr) {
        debug.info("creating window \"" + title + "\"");

        // init glfw
        if (!glfwInit()) {
            debug.error("glfw init failed");
            return;
        }

        // create context
        glfwWindowHint(GLFW_RESIZABLE, 0);
        // glfwWindowHint(GLFW_DECORATED, 0);
        m_handle = glfwCreateWindow(size.x, size.y, title.c_str(), NULL, NULL);
        if (!m_handle)
        {
            glfwTerminate();
            debug.error("window creation failed");
            return;
        }
        glfwMakeContextCurrent(m_handle);
        glfwSwapInterval(1);
        
        glfwSetWindowCloseCallback(m_handle, [](GLFWwindow* window) {
                s_handle_map.at(window)->push_event(create_window_close_request());
            }
        );
        glfwSetCursorPosCallback(m_handle, [](GLFWwindow* window, double x, double y) {
                s_handle_map.at(window)->push_event(create_mouse_move(Vec2i(x, y)));
            }
        );
        glfwSetMouseButtonCallback(m_handle, [](GLFWwindow* window, int button, int action, int mods) {
                Window_GLFW* window_glfw = s_handle_map.at(window);
                if (button == GLFW_MOUSE_BUTTON_LEFT) {
                    window_glfw->push_event(create_mouse_click(window_glfw->get_cursor_pos(), MouseButton::Left));
                }
                else if (button == GLFW_MOUSE_BUTTON_MIDDLE) {
                    window_glfw->push_event(create_mouse_click(window_glfw->get_cursor_pos(), MouseButton::Middle));
                }
                else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
                    window_glfw->push_event(create_mouse_click(window_glfw->get_cursor_pos(), MouseButton::Right));                    
                }
            }
        );
        glfwSetKeyCallback(m_handle, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
                KeyCode code = to_german_layout((KeyCode)key);
                if (action == GLFW_PRESS) {
                    s_keys_pressed.insert(code);
                    s_handle_map.at(window)->push_event(create_key_press(code, KeyState::Press));
                }
                else if (action == GLFW_REPEAT) {
                    s_handle_map.at(window)->push_event(create_key_press(code, KeyState::Repeat));
                }
                else if (action == GLFW_RELEASE) {
                    s_keys_pressed.erase(code);
                    s_handle_map.at(window)->push_event(create_key_press(code, KeyState::Release));
                }
            }
        );

        // init glew
        GLenum err = glewInit();
        if (err != GLEW_OK) {
            debug.error("glew init failed");
            return;
        }

        s_handle_map[m_handle] = this;
    }
    Window_GLFW::~Window_GLFW() {
        debug.info("destroying window \"" + title + "\"");
        s_handle_map.erase(m_handle);
        glfwDestroyWindow(m_handle);
        m_handle = nullptr;
    }

    Vec2u Window_GLFW::get_size() const {
        int width, height;
        glfwGetWindowSize(m_handle, &width, &height);
        return Vec2u(u32(width), u32(height));
    }
    void Window_GLFW::set_size(Vec2u size) {
        glfwSetWindowSize(m_handle, int(size.x), int(size.y));
    }

    Vec2i Window_GLFW::get_cursor_pos() const {
        double x_pos, y_pos;
        glfwGetCursorPos(m_handle, &x_pos, &y_pos);
        return Vec2i(floor(x_pos), floor(y_pos));
    }
    // void Window_GLFW::set_cursor_pos(Vec2i pos) {
    //     CursorMode mode = get_cursor_mode();
    //     set_cursor_mode(CursorMode::Disabled);
    //     glfwSetCursorPos(m_handle, (double)pos.x, (double)pos.y);
    //     set_cursor_mode(mode);
    // }

    void Window_GLFW::set_cursor_shape(CursorShape shape) {
        switch (shape) {
            case CursorShape::Arrow: return glfwSetCursor(m_handle, glfwCreateStandardCursor(GLFW_ARROW_CURSOR));
            case CursorShape::Hand: return glfwSetCursor(m_handle, glfwCreateStandardCursor(GLFW_HAND_CURSOR));
            case CursorShape::IBeam: return glfwSetCursor(m_handle, glfwCreateStandardCursor(GLFW_IBEAM_CURSOR));
        }
    }
    void Window_GLFW::set_cursor_mode(CursorMode mode) {
        switch (mode) {
            case CursorMode::Normal: return glfwSetInputMode(m_handle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            case CursorMode::Hidden: return glfwSetInputMode(m_handle, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
            case CursorMode::Disabled: return glfwSetInputMode(m_handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
    }
    CursorMode Window_GLFW::get_cursor_mode() {
        int mode = glfwGetInputMode(m_handle, GLFW_CURSOR);
        switch (mode) {
            case GLFW_CURSOR_NORMAL: return CursorMode::Normal;
            case GLFW_CURSOR_HIDDEN: return CursorMode::Hidden;
            case GLFW_CURSOR_DISABLED: return CursorMode::Disabled;
        }
    }

    void Window_GLFW::bind() {
        glfwMakeContextCurrent(m_handle);
    }
    void Window_GLFW::update() {
        glfwSwapBuffers(m_handle);
        glfwPollEvents();
    }

    GLFWwindow* Window_GLFW::get_handle() {
        return m_handle;
    }
}
#endif