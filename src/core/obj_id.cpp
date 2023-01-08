#include "obj_id.hpp"

namespace intern {
    ObjID::ObjID()
        : m_id(++s_obj_counter) {}
    ObjID::ObjID(const ObjID& other)
        : m_id() {}
    ObjID::ObjID(ObjID&& other)
        : m_id(other.get_id()) { other.m_id = 0; }
    void ObjID::operator=(const ObjID& other) {
        return;
    }
    void ObjID::operator=(ObjID&& other) {
        m_id = other.m_id;
        other.m_id = 0;
    }

    ID ObjID::get_id() const {
        return m_id;
    }
}