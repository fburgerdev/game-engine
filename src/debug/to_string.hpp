#pragma once
#include "math_api.hpp"
#include "event_api.hpp"
#include "utils/time.hpp"
#include "utils/trace.hpp"

namespace intern {
    // string likes
    string to_string(const string& arg);
    string to_string(const char* arg);
    string to_string(const char arg);
    
    // nums
    string to_string(const i8 arg);
    string to_string(const i16 arg);
    string to_string(const i32 arg);
    string to_string(const i64 arg);
    string to_string(const u8 arg);
    string to_string(const u16 arg);
    string to_string(const u32 arg);
    string to_string(const u64 arg);
    string to_string(const f32 arg);
    string to_string(const f64 arg);

    // location
    string to_string(const Trace& trace);

    // time
    string to_string(Timestep ts);
    string to_string(const Date& date);

    // ptr
    template<typename T>
    string to_string(const T* ptr) {
        return to_string((adress)ptr);
    }

    // event
    string to_string(KeyCode code);
    
    // math
    template<typename T, adress N>
    string to_string(const Vec<T, N>& vec) {
        string out = "(";
        for (adress i = 0; i < N - 1; ++i) {
            out += to_string(vec.at(i)) + ", ";
        }
        out += to_string(vec.at(N - 1)) + ")";
        return out;
    }
    template<typename T, adress N, adress M>
    string to_string(const Matrix<T, N, M>& mat) {
        Array<string, N> rows;
        Array<string, N> curr_col;
        for (adress m = 0; m < M; ++m) {
            adress max_size = 0;
            for (adress n = 0; n < N; ++n) {
                curr_col[n] = to_string(mat.at(n, m));
                max_size = max(curr_col[n].size(), max_size);
            }
            for (adress n = 0; n < N; ++n) {
                const adress padding = (max_size - curr_col[n].size()) / 2;
                rows[n] += " " + string(padding, ' ') + curr_col[n] + string(padding, ' ');
            }
            for (adress n = 0; n < N; ++n) {
                max_size = max(rows[n].size(), max_size);
            }
            for (adress n = 0; n < N; ++n) {
                rows[n] += string(max_size - rows[n].size(), ' ') + " │";
            }
        }
    
        string out;
        for (const string& row : rows) {
            out += "│" + row + "\n";
        }
        return out;
    }

    // data structures
    template<typename T>
    string to_string(const List<T>& list) {
        string out = "List:\n";
        for (const T& val : list) {
            out += "\t" + to_string(val) + "\n";
        }
        return out;
    }
    template<typename Key, typename Val>
    string to_string(const Map<Key, Val>& map) {
        string out = "Map:\n";
        for (const auto&[key, val] : map) {
            out += "\t" + to_string(key) + " -> " + to_string(val) + "\n";
        }
        return out;
    }
    template<typename T>
    string to_string(const Set<T>& set) {
        string out = "Set:\n";
        for (const T& val : set) {
            out += "\t" + to_string(val) + "\n";
        }
        return out;
    }
}