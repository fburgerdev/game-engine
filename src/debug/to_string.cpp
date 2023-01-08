#include "to_string.hpp"

namespace intern {
  	// string likes
  	string to_string(const string& arg) {
    	return arg;
  	}
  	string to_string(const char* arg) {
    	return string(arg);
  	}
  	string to_string(const char arg) {
    	return string() += arg;
  	}

	// nums
  	string to_string(const i8 arg) {
    	return std::to_string(arg);
  	}
  	string to_string(const i16 arg) {
		return std::to_string(arg);
	}
  	string to_string(const i32 arg) {
		return std::to_string(arg);
	}
  	string to_string(const i64 arg) {
		return std::to_string(arg);
	}
  	string to_string(const u8 arg) {
		return std::to_string(arg);
	}
  	string to_string(const u16 arg) {
		return std::to_string(arg);
	}
  	string to_string(const u32 arg) {
    	return std::to_string(arg);
	}
  	string to_string(const u64 arg) {
		return std::to_string(arg);
	}
  	string to_string(const f32 arg) {
		return std::to_string(arg);
	}
  	string to_string(const f64 arg) {
		return std::to_string(arg);
	}

	// location
    string to_string(const Trace& trace) {
		string func_name = to_string(trace.stack.top());
		adress to = func_name.find_first_of('(');
		adress from = func_name.find_last_of(' ') + 1;
		return func_name.substr(0, to) + "[" + to_string(trace.line) + ":" + to_string(trace.column) + "]";
	}

  	// time
    string to_string(Timestep ts) {
		return to_string(ts.sec()) + "sec";
	}
  	string to_string(const Date& date) {
    	string hr = to_string(date.hr);
    	string min = to_string(date.min);
    	string sec = to_string(date.sec);
    	string ms = to_string(date.ms);
    	return "[" + string(2 - hr.size(), '0') + hr + ":" + string(2 - min.size(), '0') + min + ":" + string(2 - sec.size(), '0') + sec + ":" + string(3 - ms.size(), '0') + ms + "]";
  	}

	// events
	string to_string(KeyCode code) {
		switch (code) {
			case KeyCode::KEY_GER_ESZETT: return "KEY_GER_ESZETT";
			case KeyCode::KEY_GER_UMLAUT_U: return "KEY_GER_UMLAUT_U";
			case KeyCode::KEY_GER_UMLAUT_O: return "KEY_GER_UMLAUT_O";
			case KeyCode::KEY_GER_UMLAUT_A: return "KEY_GER_UMLAUT_A";
			case KeyCode::KEY_ADD: return "KEY_ADD";
			case KeyCode::KEY_HASH: return "KEY_HASH";

			case KeyCode::KEY_UNKNOWN: return "KEY_UNKNOWN";
			case KeyCode::KEY_SPACE: return "KEY_SPACE";
			case KeyCode::KEY_APOSTROPHE: return "KEY_APOSTROPHE";
			case KeyCode::KEY_COMMA: return "KEY_COMMA";
			case KeyCode::KEY_MINUS: return "KEY_MINUS";
			case KeyCode::KEY_PERIOD: return "KEY_PERIOD";
			case KeyCode::KEY_SLASH: return "KEY_SLASH";
			case KeyCode::KEY_0: return "KEY_0";
			case KeyCode::KEY_1: return "KEY_1";
			case KeyCode::KEY_2: return "KEY_2";
			case KeyCode::KEY_3: return "KEY_3";
			case KeyCode::KEY_4: return "KEY_4";
			case KeyCode::KEY_5: return "KEY_5";
			case KeyCode::KEY_6: return "KEY_6";
			case KeyCode::KEY_7: return "KEY_7";
			case KeyCode::KEY_8: return "KEY_8";
			case KeyCode::KEY_9: return "KEY_9";
			case KeyCode::KEY_SEMICOLON: return "KEY_SEMICOLON";
			case KeyCode::KEY_EQUAL: return "KEY_EQUAL";
			case KeyCode::KEY_A: return "KEY_A";
			case KeyCode::KEY_B: return "KEY_B";
			case KeyCode::KEY_C: return "KEY_C";
			case KeyCode::KEY_D: return "KEY_D";
			case KeyCode::KEY_E: return "KEY_E";
			case KeyCode::KEY_F: return "KEY_F";
			case KeyCode::KEY_G: return "KEY_G";
			case KeyCode::KEY_H: return "KEY_H";
			case KeyCode::KEY_I: return "KEY_I";
			case KeyCode::KEY_J: return "KEY_J";
			case KeyCode::KEY_K: return "KEY_K";
			case KeyCode::KEY_L: return "KEY_L";
			case KeyCode::KEY_M: return "KEY_M";
			case KeyCode::KEY_N: return "KEY_N";
			case KeyCode::KEY_O: return "KEY_O";
			case KeyCode::KEY_P: return "KEY_P";
			case KeyCode::KEY_Q: return "KEY_Q";
			case KeyCode::KEY_R: return "KEY_R";
			case KeyCode::KEY_S: return "KEY_S";
			case KeyCode::KEY_T: return "KEY_T";
			case KeyCode::KEY_U: return "KEY_U";
			case KeyCode::KEY_V: return "KEY_V";
			case KeyCode::KEY_W: return "KEY_W";
			case KeyCode::KEY_X: return "KEY_X";
			case KeyCode::KEY_Y: return "KEY_Y";
			case KeyCode::KEY_Z: return "KEY_Z";
			case KeyCode::KEY_LEFT_BRACKET: return "KEY_LEFT_BRACKET";
			case KeyCode::KEY_BACKSLASH: return "KEY_BACKSLASH";
			case KeyCode::KEY_RIGHT_BRACKET: return "KEY_RIGHT_BRACKET";
			case KeyCode::KEY_GRAVE_ACCENT: return "KEY_GRAVE_ACCENT";
			case KeyCode::KEY_WORLD_1: return "KEY_WORLD_1";
			case KeyCode::KEY_WORLD_2: return "KEY_WORLD_2";
			case KeyCode::KEY_ESCAPE: return "KEY_ESCAPE";
			case KeyCode::KEY_ENTER: return "KEY_ENTER";
			case KeyCode::KEY_TAB: return "KEY_TAB";
			case KeyCode::KEY_BACKSPACE: return "KEY_BACKSPACE";
			case KeyCode::KEY_INSERT: return "KEY_INSERT";
			case KeyCode::KEY_DELETE: return "KEY_DELETE";
			case KeyCode::KEY_RIGHT: return "KEY_RIGHT";
			case KeyCode::KEY_LEFT: return "KEY_LEFT";
			case KeyCode::KEY_DOWN: return "KEY_DOWN";
			case KeyCode::KEY_UP: return "KEY_UP";
			case KeyCode::KEY_PAGE_UP: return "KEY_PAGE_UP";
			case KeyCode::KEY_PAGE_DOWN: return "KEY_PAGE_DOWN";
			case KeyCode::KEY_HOME: return "KEY_HOME";
			case KeyCode::KEY_END: return "KEY_END";
			case KeyCode::KEY_CAPS_LOCK: return "KEY_CAPS_LOCK";
			case KeyCode::KEY_SCROLL_LOCK: return "KEY_SCROLL_LOCK";
			case KeyCode::KEY_NUM_LOCK: return "KEY_NUM_LOCK";
			case KeyCode::KEY_PRINT_SCREEN: return "KEY_PRINT_SCREEN";
			case KeyCode::KEY_PAUSE: return "KEY_PAUSE";
			case KeyCode::KEY_F1: return "KEY_F1";
			case KeyCode::KEY_F2: return "KEY_F2";
			case KeyCode::KEY_F3: return "KEY_F3";
			case KeyCode::KEY_F4: return "KEY_F4";
			case KeyCode::KEY_F5: return "KEY_F5";
			case KeyCode::KEY_F6: return "KEY_F6";
			case KeyCode::KEY_F7: return "KEY_F7";
			case KeyCode::KEY_F8: return "KEY_F8";
			case KeyCode::KEY_F9: return "KEY_F9";
			case KeyCode::KEY_F10: return "KEY_F10";
			case KeyCode::KEY_F11: return "KEY_F11";
			case KeyCode::KEY_F12: return "KEY_F12";
			case KeyCode::KEY_F13: return "KEY_F13";
			case KeyCode::KEY_F14: return "KEY_F14";
			case KeyCode::KEY_F15: return "KEY_F15";
			case KeyCode::KEY_F16: return "KEY_F16";
			case KeyCode::KEY_F17: return "KEY_F17";
			case KeyCode::KEY_F18: return "KEY_F18";
			case KeyCode::KEY_F19: return "KEY_F19";
			case KeyCode::KEY_F20: return "KEY_F20";
			case KeyCode::KEY_F21: return "KEY_F21";
			case KeyCode::KEY_F22: return "KEY_F22";
			case KeyCode::KEY_F23: return "KEY_F23";
			case KeyCode::KEY_F24: return "KEY_F24";
			case KeyCode::KEY_F25: return "KEY_F25";
			case KeyCode::KEY_KP_0: return "KEY_KP_0";
			case KeyCode::KEY_KP_1: return "KEY_KP_1";
			case KeyCode::KEY_KP_2: return "KEY_KP_2";
			case KeyCode::KEY_KP_3: return "KEY_KP_3";
			case KeyCode::KEY_KP_4: return "KEY_KP_4";
			case KeyCode::KEY_KP_5: return "KEY_KP_5";
			case KeyCode::KEY_KP_6: return "KEY_KP_6";
			case KeyCode::KEY_KP_7: return "KEY_KP_7";
			case KeyCode::KEY_KP_8: return "KEY_KP_8";
			case KeyCode::KEY_KP_9: return "KEY_KP_9";
			case KeyCode::KEY_KP_DECIMAL: return "KEY_KP_DECIMAL";
			case KeyCode::KEY_KP_DIVIDE: return "KEY_KP_DIVIDE";
			case KeyCode::KEY_KP_MULTIPLY: return "KEY_KP_MULTIPLY";
			case KeyCode::KEY_KP_SUBTRACT: return "KEY_KP_SUBTRACT";
			case KeyCode::KEY_KP_ADD: return "KEY_KP_ADD";
			case KeyCode::KEY_KP_ENTER: return "KEY_KP_ENTER";
			case KeyCode::KEY_KP_EQUAL: return "KEY_KP_EQUAL";
			case KeyCode::KEY_LEFT_SHIFT: return "KEY_LEFT_SHIFT";
			case KeyCode::KEY_LEFT_CONTROL: return "KEY_LEFT_CONTROL";
			case KeyCode::KEY_LEFT_ALT: return "KEY_LEFT_ALT";
			case KeyCode::KEY_LEFT_SUPER: return "KEY_LEFT_SUPER";
			case KeyCode::KEY_RIGHT_SHIFT: return "KEY_RIGHT_SHIFT";
			case KeyCode::KEY_RIGHT_CONTROL: return "KEY_RIGHT_CONTROL";
			case KeyCode::KEY_RIGHT_ALT: return "KEY_RIGHT_ALT";
			case KeyCode::KEY_RIGHT_SUPER: return "KEY_RIGHT_SUPER";
			case KeyCode::KEY_MENU: return "KEY_MENU";
		}
		return "ERROR";
	}
}