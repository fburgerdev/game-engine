#include "time.hpp"
#include <chrono>
#include <thread>

namespace intern {
    // Timestep
    Timestep::Timestep(f32 sec)
        : m_sec(sec) {}
    Timestep::operator f32() const {
        return sec();
    }
    f32 Timestep::sec() const {
        return m_sec;
    }
    f32 Timestep::ms() const {
        return m_sec * 1000;
    }
    f32 Timestep::us() const {
        return m_sec * 1000000;
    }

    Timestep sec(f32 seconds) {
        return seconds;
    }
    Timestep ms(f32 milliseconds) {
        return milliseconds / 1e3;
    }
    Timestep us(f32 microseconds) {
        return microseconds / 1e6;
    }
    void wait(Timestep time) {
        std::this_thread::sleep_for(std::chrono::milliseconds(i64(time.ms())));
    }

    // Stopwatch
    Stopwatch::Stopwatch() {
        reset();
    }
    void Stopwatch::reset() {
        m_start = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    }
    Timestep Stopwatch::time() const {
        i64 elapsed = std::chrono::high_resolution_clock::now().time_since_epoch().count() - m_start;
        return f32(f64(elapsed) / 1e9);
    }

    // Date
    Date Date::now() {
        const auto now = std::chrono::system_clock::now();
        const auto secs = std::chrono::time_point_cast<std::chrono::seconds>(now);
        const auto fraction = now - secs;
        const auto time = std::chrono::system_clock::to_time_t(now);
        const auto date = *localtime(&time);

        Date out;
        out.year = date.tm_year;
        out.month = date.tm_mon;
        out.day = date.tm_mday;
        out.hr = date.tm_hour;
        out.min = date.tm_min;
        out.sec = date.tm_sec;
        out.ms = std::chrono::duration_cast<std::chrono::milliseconds>(fraction).count();
        
        return out;
    }
}