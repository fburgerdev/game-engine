#include "async.hpp"
#include <thread>

namespace intern {
    void async_call(std::function<void()> func) {
        std::thread(func).detach();
    }
}