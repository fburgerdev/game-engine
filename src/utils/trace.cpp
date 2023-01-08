#include "trace.hpp"

namespace intern {
    Trace::Trace(const std::source_location& location) 
        : file(location.file_name()), stack({ location.function_name() }), line(location.line()), column(location.column()) {}
    bool operator==(const Trace& trace1, const Trace& trace2) {
        return trace1.file == trace2.file && trace1.line == trace2.line && trace1.column == trace2.column;
    }
}