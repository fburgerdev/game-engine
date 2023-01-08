#pragma once
#include <memory>
#include <unordered_map>
#include <vector>
#include <set>
#include <stack>
#include <queue>
#include <array>
#include <string>

namespace intern {
    // primitive dtypes
    using i8 = std::int8_t;
    using i16 = std::int16_t;
    using i32 = std::int32_t;
    using i64 = std::int64_t;
    using u8 = std::uint8_t;
    using u16 = std::uint16_t;
    using u32 = std::uint32_t;
    using u64 = std::uint64_t;
    using f32 = float;
    using f64 = double;
    using byte = unsigned char;
    using string = std::string;
    using adress = std::size_t;

    // data structure
    template<typename Key, typename Val>
    using Map = std::unordered_map<Key, Val>;
    template<typename T>
    using List = std::vector<T>;
    template<typename T>
    using Set = std::set<T>;
    template<typename T>
    using Stack = std::stack<T>;
    template<typename T>
    using Queue = std::queue<T>;
    template<typename T, adress N>
    using Array = std::array<T, N>;
}