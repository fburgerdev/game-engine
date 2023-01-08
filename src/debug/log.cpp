#include "log.hpp"
#include "to_string.hpp"
#include <iostream>

namespace intern {
    Logger::Logger(u8 output)
        : m_output(output), m_is_muted(false) {}
    Logger::Logger(Output output)
        : m_output((u8)output), m_is_muted(false) {}
    void Logger::trace(const Trace& trace) {
        m_messages.emplace(MsgType::Log, trace);
        log_msg(m_messages.back());
    }
    void Logger::log_msg(const Msg& msg) {
        if (m_messages.size() > 1000) {
            m_messages.pop();
        }
        
        if (m_is_muted) {
            return;
        }
        if (m_output | (u8)Output::Console) {
            std::cout << "\033[37m";
            string col;
            switch (msg.type)
            {
            case MsgType::Log:
                col = "\033[0m";
                std::cout << "Log";
                break;
            case MsgType::Info:
                col = "\033[32m";
                std::cout << "Info";
                break;
            case MsgType::Warning:
                col = "\033[33m";
                std::cout << "Warning";
                break;
            case MsgType::Error:
                col = "\033[31m";
                std::cout << "Error";
                break;
            default:
                break;
            }
            std::cout << to_string(msg.date) << ":";
            if (msg.trace.stack.size() > 0) {
                std::cout << " " << to_string(msg.trace);
            }
            if (msg.body.size() > 0) {
                std::cout << "\n\033[37m>>>> " << col;
            }
            for (adress i = 0; i < msg.body.size(); ++i) {
                std::cout.put(msg.body[i]);
                if (i != msg.body.size() - 1 && msg.body[i] == '\n') {
                    std::cout << "\033[37m>>>> " << col;
                }
            }
            if (msg.body.back() != '\n') {
                std::cout.put('\n');      
            }
            std::cout << "\033[0m";
            std::cout.flush();
        }
    }
    void Logger::mute() {
        m_is_muted = true;
    }
    void Logger::unmute() {
        m_is_muted = false;
    }
}