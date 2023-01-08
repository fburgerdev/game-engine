#pragma once
#include "msg.hpp"

namespace intern {
    class Logger {
    public:
        enum class Output : u8 {
            Console = 1,
            File = 2
        };

        Logger(u8 output);
        Logger(Logger::Output output);
    
        template<typename... TArgs>
        void log(const TArgs&... args) {
            m_messages.emplace(MsgType::Log, args...);
            log_msg(m_messages.back());
        }
        template<typename... TArgs>
        void info(const TArgs&... args) {
            m_messages.emplace(MsgType::Info, args...);
            log_msg(m_messages.back());
        }
        template<typename... TArgs>
        void warn(const TArgs&... args) {
            m_messages.emplace(MsgType::Warning, args...);
            log_msg(m_messages.back());
        }
        template<typename... TArgs>
        void error(const TArgs&... args) {
            m_messages.emplace(MsgType::Error, args...);
            log_msg(m_messages.back());
        }

        void trace(const Trace& trace = Trace(std::source_location::current()));
        template<typename T>
        void trace(const T& arg, const Trace& trace = Trace(std::source_location::current())) {
            m_messages.emplace(MsgType::Error, trace, arg);
            log_msg(m_messages.back());
        }

        void mute();
        void unmute();
    private:
        void log_msg(const Msg& msg);
    private:
        u8 m_output;
        bool m_is_muted;
        Queue<Msg> m_messages;
    };

    static inline Logger debug = Logger(Logger::Output::Console);
}