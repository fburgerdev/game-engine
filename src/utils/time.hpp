#pragma once
#include "common.hpp"

namespace intern {
    struct Timestep {
    public:
        Timestep(f32 sec = 0);
        operator f32() const;

        f32 sec() const;
        f32 ms() const;
        f32 us() const;
    private:
        f32 m_sec;
    };
    Timestep sec(f32 seconds);
    Timestep ms(f32 milliseconds);
    Timestep us(f32 microseconds);
    void wait(Timestep time);

    class Stopwatch {
    public:
        Stopwatch();

        void reset();
        Timestep time() const;
    private:
        i64 m_start;
    };

    struct Date {
        static Date now();

        u32 year;
        u32 month;
        u32 day;

        u32 hr;
        u32 min;
        u32 sec;
        u32 ms;
    };
}