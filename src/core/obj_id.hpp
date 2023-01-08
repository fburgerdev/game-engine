#pragma once
#include "common.hpp"
#include <type_traits>

namespace intern {
    using ID = u64;
    struct ObjID {
    public:
        ObjID();
        ObjID(const ObjID& other);
        ObjID(ObjID&& other);
        void operator=(const ObjID& other);
        void operator=(ObjID&& other);

        ID get_id() const;
    private:
        static inline u64 s_obj_counter = 0;
        ID m_id;
    };
    
    template<typename T, typename... Args>
    T& emplace_in_map(Map<ID, T>& map, Args&&... args) {
        ObjID obj_id;
        return map.try_emplace(obj_id.get_id(), std::move(obj_id), args...).first->second;
    }

    // compare
    template<typename T,
        std::enable_if<std::is_base_of<T, ObjID>::value, bool> = true>
    bool operator==(const T& obj1, const T& obj2) {
        return obj1.get_id() == obj2.get_id();
    }
    template<typename T,
        std::enable_if<std::is_base_of<T, ObjID>::value, bool> = true>
    bool operator!=(const T& obj1, const T& obj2) {
        return obj1.get_id() != obj2.get_id();
    }
    template<typename T,
        std::enable_if<std::is_base_of<T, ObjID>::value, bool> = true>
    bool operator<(const T& obj1, const T& obj2) {
        return obj1.get_id() < obj2.get_id();
    }
    template<typename T,
    std::enable_if<std::is_base_of<T, ObjID>::value, bool> = true>
    bool operator<=(const T& obj1, const T& obj2) {
        return obj1.get_id() <= obj2.get_id();
    }
    template<typename T,
        std::enable_if<std::is_base_of<T, ObjID>::value, bool> = true>
    bool operator>(const T& obj1, const T& obj2) {
        return obj1.get_id() > obj2.get_id();
    }
    template<typename T,
        std::enable_if<std::is_base_of<T, ObjID>::value, bool> = true>
    bool operator>=(const T& obj1, const T& obj2) {
        return obj1.get_id() >= obj2.get_id();
    }
}