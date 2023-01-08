#include "event.hpp"

namespace intern {
    KeyCode to_german_layout(KeyCode code) {
        switch (code)
        {
            case KeyCode::KEY_Y: return KeyCode::KEY_Z;
            case KeyCode::KEY_Z: return KeyCode::KEY_Y;
            case KeyCode::KEY_MINUS: return KeyCode::KEY_GER_ESZETT;
            case KeyCode::KEY_EQUAL: return KeyCode::KEY_APOSTROPHE;
            case KeyCode::KEY_LEFT_BRACKET: return KeyCode::KEY_GER_UMLAUT_U;
            case KeyCode::KEY_BACKSLASH: return KeyCode::KEY_HASH;
            case KeyCode::KEY_RIGHT_BRACKET: return KeyCode::KEY_ADD;
            case KeyCode::KEY_SEMICOLON: return KeyCode::KEY_GER_UMLAUT_O;
            case KeyCode::KEY_APOSTROPHE: return KeyCode::KEY_GER_UMLAUT_A;
            case KeyCode::KEY_SLASH: return KeyCode::KEY_MINUS;
            default: return code;
        }
    }

    // event
    Event::Event(EventType type)
        : type(type) {}
    Event create_mouse_move(Vec2i pos) {
        Event out(EventType::MouseMove);
        out.mouse_move.pos = pos;
        return out;
    }
    Event create_mouse_click(Vec2i pos, MouseButton button) {
        Event out(EventType::MouseClick);
        out.mouse_click.pos = pos;
        out.mouse_click.button = button;
        return out;
    }
    Event create_mouse_release(Vec2i pos, MouseButton button) {
        Event out(EventType::MouseRelease);
        out.mouse_release.pos = pos;
        out.mouse_release.button = button;
        return out;
    }
    Event create_key_press(KeyCode code, KeyState state) {
        Event out(EventType::KeyPress);
        out.key_press.code = code;
        out.key_press.state = state;
        return out;
    }
    Event create_window_close_request() {
        return Event(EventType::WindowCloseRequest);
    }
}