#include "msg.hpp"

namespace intern {
    void Msg::push_body() {

    }
    bool operator==(const Msg& msg1, const Msg& msg2) {
        return msg1.trace == msg2.trace && msg1.body == msg2.body;
    }
}