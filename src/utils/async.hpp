#pragma once
#include "time.hpp"
#include <functional>

namespace intern {
    void async_call(std::function<void()> func);
    template<typename Func, typename... Args>
    void async_call(std::function<void(Args...)> func, Args... args) {
        async_call(static_cast<std::function<void()>>([=] { func(args...); }));
    }
    template<typename Func, typename... Args>
    void invoke(Timestep time, Func func, Args... args) {
        async_call(static_cast<std::function<void()>>([=]{ wait(time); func(args...); }));
    }
}