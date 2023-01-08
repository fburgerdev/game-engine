#pragma once
#include "common.hpp"
#include <source_location>

namespace intern {
    struct Trace {
        Trace() = default;
        Trace(const std::source_location& location);

        string file;
        Stack<string> stack;
        u32 line;
        u32 column;
    };
    bool operator==(const Trace& trace1, const Trace& trace2);

    #define TRACE Trace(std::source_location::current())
}