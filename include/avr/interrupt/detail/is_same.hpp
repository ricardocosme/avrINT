#pragma once

#include "avr/interrupt/detail/integral_constant.hpp"

namespace avr { namespace interrupt { namespace detail {

template<typename T1, typename T2>
struct is_same : false_type {};

template<typename T1>
struct is_same<T1, T1> : true_type {};

}}}
