#include "arithmetic.hpp"
#include <math.h>

namespace intern {
    i8 abs(i8 x) {
        return x < 0 ? -x : x;
    }
    i16 abs(i16 x) {
        return x < 0 ? -x : x;
    }
    i32 abs(i32 x) {
        return x < 0 ? -x : x;
    }
    i64 abs(i64 x) {
        return x < 0 ? -x : x;
    }
    f32 abs(f32 x) {
        return x < 0 ? -x : x;
    }
    f64 abs(f64 x) {
        return x < 0 ? -x : x;
    }

    f32 floor(f32 x) {
        return f32(i32(x));
    }
    f64 floor(f64 x) {
        return f32(i32(x));
    }

    f32 ceil(f32 x) {
        return f32(i32(x + 1));
    }
    f64 ceil(f64 x) {
        return f32(i32(x + 1));
    }

    f32 max(f32 x, f64 y) {
        return x < y ? y : x;
    }
    f64 max(f64 x, f64 y) {
        return x < y ? y : x;
    }

    f32 min(f32 x, f64 y) {
        return x < y ? x : y;
    }
    f64 min(f64 x, f64 y) {
        return x < y ? x : y;
    }

    f32 sin(f32 x) {
		return std::sin(x);
	}
    f64 sin(f64 x) {
		return std::sin(x);
	}
    f32 cos(f32 x) {
		return std::cos(x);
	}
    f64 cos(f64 x) {
		return std::cos(x);
	}
    f32 tan(f32 x) {
		return std::tan(x);
	}
    f64 tan(f64 x) {
		return std::tan(x);
	}
    f32 asin(f32 x) {
		return std::asin(x);
	}
    f64 asin(f64 x) {
		return std::asin(x);
	}
    f32 acos(f32 x) {
		return std::acos(x);
	}
    f64 acos(f64 x) {
		return std::acos(x);
	}
    f32 atan(f32 x) {
		return std::atan(x);
	}
    f64 atan(f64 x) {
		return std::atan(x);
	}

    f32 exp(f32 x) {
		return std::exp(x);
	}
    f64 exp(f64 x) {
		return std::exp(x);
	}
    f32 ln(f32 x) {
		return std::log(x);
	}
    f64 ln(f64 x) {
		return std::log(x);
	}
    f32 log2(f32 x) {
        return std::log2(x);
    }
    f64 log2(f64 x) {
        return std::log2(x);
    }
    f32 log10(f32 x) {
        return std::log10(x);
    }
    f64 log10(f64 x) {
        return std::log10(x);
    }
    f32 pow(f32 base, f32 exponent) {
        return std::pow(base, exponent);
    }
    f64 pow(f64 base, f64 exponent) {
        return std::pow(base, exponent);
    }
    f32 pow2(f32 x) {
        return x * x;
    }
    f64 pow2(f64 x) {
        return x * x;
    }
    f32 pow3(f32 x) {
        return x * x * x;
    }
    f64 pow3(f64 x) {
        return x * x * x;
    }
}