#pragma once

namespace avr { namespace interrupt { namespace detail {

template<typename T, T v>
struct integral_constant {
    static constexpr T value = v;
    using value_type = T;
    using type = integral_constant;
};

struct true_type { static constexpr bool value = true; };
struct false_type { static constexpr bool value = false; };

}}}
