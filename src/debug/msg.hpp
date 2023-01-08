#pragma once
#include "common.hpp"
#include "utils/trace.hpp"
#include "utils/time.hpp"

namespace intern {
    enum class MsgType : u8 {
        Log = 1,
        Info = 2,
        Warning = 4,
        Error = 8
    };
    struct Msg {
    public:
        template<typename... TArgs>
        Msg(MsgType type, const TArgs&... args)
            : date(Date::now()), trace(), type(type), body() {
            push_body(args...);
        }
        template<typename... TArgs>
        Msg(MsgType type, const Trace& trace, const TArgs&... args)
            : date(Date::now()), trace(trace), type(type), body() {
            push_body(args...);
        }

        Date date;
        Trace trace;
        MsgType type;

        string body;
    private:
        void push_body();
        template<typename TFirst, typename... TRest>
        void push_body(const TFirst& arg, const TRest&... rest) {
            body += to_string(arg);
            if constexpr (sizeof...(TRest) > 0) {
                if (body.back() != '\n') {
                    body.push_back(' ');
                }
                push_body(rest...);
            }
        }
    };
    bool operator==(const Msg& msg1, const Msg& msg2);
}