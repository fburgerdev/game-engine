#pragma once
#include "core_api.hpp"
#include "scene_api.hpp"
#include "event_api.hpp"
#include "asset_manager/parrot_source.hpp"

namespace intern {
    enum class CursorShape {
        Arrow, Hand, IBeam 
    };
    enum class CursorMode {
        Normal, Hidden, Disabled 
    };

    class Window : public ObjID {
    public:
        Window(const string& title);
        virtual ~Window() {}

        void close();
        bool is_open() const;

        List<Scene>& get_scenes();
        const List<Scene>& get_scenes() const;
        Scene& get_scene(const string& name = "Scene");
        Scene& push_scene();
        Scene& push_scene_from_src(const ParrotSource& src);

        Event pop_event();
        void push_event(Event e);
        bool has_events() const;

        virtual Vec2u get_size() const = 0;
        virtual void set_size(Vec2u size) = 0;
        
        virtual Vec2i get_cursor_pos() const = 0;
        // virtual void set_cursor_pos(Vec2i pos) = 0;
        virtual void set_cursor_shape(CursorShape shape) = 0;
        virtual void set_cursor_mode(CursorMode mode) = 0;
        virtual CursorMode get_cursor_mode() = 0;

        virtual void bind() = 0;
        virtual void update() = 0;

        string title;
    private:
        List<Scene> m_scenes;
        Queue<Event> m_events;
        bool m_close;
    };
}