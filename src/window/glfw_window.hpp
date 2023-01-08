#pragma once
#include "window.hpp"

struct GLFWwindow;
namespace intern {
    class Window_GLFW : public Window {
    public:
        Window_GLFW(const string& title, Vec2u size);
        virtual ~Window_GLFW();

        virtual Vec2u get_size() const override;
        virtual void set_size(Vec2u size) override;

        virtual Vec2i get_cursor_pos() const override;
        // virtual void set_cursor_pos(Vec2i pos) override;
        virtual void set_cursor_shape(CursorShape shape) override;
        virtual void set_cursor_mode(CursorMode mode) override;
        virtual CursorMode get_cursor_mode() override;

        virtual void bind() override;
        virtual void update() override;

        GLFWwindow* get_handle();
    private:
        GLFWwindow* m_handle;
    };
}