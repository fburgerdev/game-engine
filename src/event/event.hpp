#pragma once
#include "config.hpp"
#include "math_api.hpp"

#if PT_WINDOW_API == PT_GLFW
#include "glfw_keycodes.hpp"
#endif

namespace intern {
    enum class MouseButton {
        Left, Middle, Right
    };
    enum class KeyState {
        Press, Release, Repeat
    };   

    KeyCode to_german_layout(KeyCode code);
    bool is_key_pressed(KeyCode code);
    enum class EventType {
        None = 0,
    
        // window events
        MouseMove,
        MouseClick,
        MouseRelease,
        KeyPress,
        KeyHold,
        KeyRelease,
        WindowCloseRequest,
        WindowResize
    };
    struct Event {
        Event(EventType type);

        EventType type;
        union
        {
            struct { Vec2i pos; } mouse_move;
            struct { Vec2i pos; MouseButton button; } mouse_click;
            struct { Vec2i pos; MouseButton button; } mouse_release;
            struct { KeyCode code; KeyState state; } key_press;
        };
    };
    Event create_mouse_move(Vec2i pos);
    Event create_mouse_click(Vec2i pos, MouseButton button);
    Event create_mouse_release(Vec2i pos, MouseButton button);
    Event create_key_press(KeyCode code, KeyState state);
    Event create_window_close_request();
}