#pragma once

#include "avr/interrupt/detail/global.hpp"
#include "avr/interrupt/detail/is_same.hpp"

#include <stdint.h>
#if __has_include(<avr/io.hpp>)
#include <avr/io.hpp>
#else
#include <avr/io.h> //We use avr-libc if avrIO isn't available.
namespace avr { namespace io {
#if __cplusplus >= 201703L
inline volatile uint8_t& sreg{SREG};
#else
namespace {
volatile uint8_t& sreg{SREG};
}//anonymous namespace
#endif
}}
#endif

//We need to undef the macros defined by avr-libc to avoid collision
//when <avr/interrupt.h> is included before this header.
#undef cli
#undef sei

namespace avr { namespace interrupt {

/** Enable the global interrupts */
[[gnu::always_inline]] inline void on() noexcept
{ asm("sei" ::: "memory"); }

/** Enable the global interrupts */
[[gnu::always_inline]] inline void sei() noexcept
{ on(); }

/** Disable the global interrupts */
[[gnu::always_inline]] inline void off() noexcept
{ asm("cli" ::: "memory"); }

/** Disable the global interrupts */
[[gnu::always_inline]] inline void cli() noexcept
{ off(); }

inline void clobber() {}

template<typename T, typename... Rest>
[[gnu::always_inline]] inline void clobber(const T& v, Rest&... rest) {
    asm("" : : "g"(v) : "memory");
    clobber(rest...);
}

/** Tag to be used as a parameter to the constructor of the class
 * 'atomic'. It informs that the status register state should be
 * recovered at the end of the atomic scope. */
struct restore_t{};

/** Tag to be used as a parameter to the constructor of the class
 * 'atomic'. It informs that the global interrupts must always be
 * enabled at the end of the scope. */
struct on_at_the_end_t{};

/** RAII to execute code without being disturbed by interrupts 
    
    By default the state of the status register that was before the
    atomic scope is recovered at the end of the scope, which means
    that interruptions are enabled only if they were enabled
    before. If the argument 'on_at_the_end' is passed then the
    interruptions are always enabled at the end of the scope.

    Example:
      {
        atomic sa; //same as 'atomic sa(restore)'
        //my code
      }
   
      {
        atomic sa(on_at_the_end);
        //my code
      }

    Note, the compiler optimizer can reorder instructions around the
    atomic scope when that instructions doesn't have observable side
    effects. Take a look at 'reordering_code.org' to know more about
    it.

    [optional] clobbers: list of lvalues that can have an observable
    side effect. This should only be used to do fine adjustments in
    the generated code in order to move to the outside of the atomic
    section some code that does't need to be there and, first of
    all, when the timing is a critical factor.
*/
template<typename AtTheEnd = restore_t>
class atomic {
    uint8_t _sreg;
public:
    constexpr static bool is_restore
        {detail::is_same<AtTheEnd, restore_t>::value};

    template<typename... Clobbers>
    explicit atomic(AtTheEnd = AtTheEnd{}, Clobbers&... clobbers) {
        clobber(clobbers...);
        if(is_restore) _sreg = io::sreg;
        off();
    }
    
    ~atomic() {
        if(is_restore) io::sreg = _sreg;
        else on();
    }
};

/** Tag to be used as a parameter to the constructor of the class
 * 'interruptible'. It informs that the global interrupts must always
 * be disabled at the end of the scope. */
struct off_at_the_end_t{};

/** RAII to turn on interruptions in the beginning and restore SREG
    state or turn off at the end.
    
    By default the state of the status register that was before the
    interruptible scope is recovered at the end of the scope, which
    means that interruptions are disabled only if they were disabled
    before. If the argument 'off_at_the_end' is passed then the
    interruptions are always disabled at the end of the scope.

    Example:
      {
        interruptible si; //same as 'interruptible sa(restore)'
        //my code
      }
   
      {
        interruptible si(off_at_the_end);
        //my code
      }

    Note, the compiler optimizer can reorder instructions around the
    interruptible scope when that instructions doesn't have observable
    side effects. Take a look at 'reordering_code.org' to know more
    about it.

    [optional] clobbers: list of lvalues that can have an observable
    side effect. This should only be used to do fine adjustments in
    the generated code in order to move to the outside of the atomic
    section some code that does't need to be there and, first of
    all, when the timing is a critical factor.
*/
template<typename AtTheEnd = restore_t>
class interruptible {
    uint8_t _sreg;
public:
    constexpr static bool is_restore
        {detail::is_same<AtTheEnd, restore_t>::value};

    template<typename... Clobbers>
    explicit interruptible(AtTheEnd = AtTheEnd{}, Clobbers&... clobbers) {
        clobber(clobbers...);
        if(is_restore) _sreg = io::sreg;
        on();
    }
    
    ~interruptible() {
        if(is_restore) io::sreg = _sreg;
        else off();
    }
};

#if __cplusplus >= 201703L
inline constexpr restore_t restore;
inline constexpr on_at_the_end_t on_at_the_end;
inline constexpr off_at_the_end_t off_at_the_end;
#else
namespace {
constexpr auto& restore{detail::global<restore_t>::instance};
constexpr auto& on_at_the_end{detail::global<on_at_the_end_t>::instance};
constexpr auto& off_at_the_end{detail::global<off_at_the_end_t>::instance};
}//anonymous namespace
#endif

/** [C++11/14] The atomic ctor should be use if C++17 is available. */
template<typename AtTheEnd = restore_t>
[[gnu::always_inline, nodiscard]]
inline atomic<AtTheEnd> make_atomic(AtTheEnd = AtTheEnd{}) noexcept
{ return atomic<AtTheEnd>{}; }

/** [C++11/14] The interruptinle ctor should be use if C++17 is available. */
template<typename AtTheEnd = restore_t>
[[gnu::always_inline, nodiscard]]
inline interruptible<AtTheEnd> make_interruptible(AtTheEnd = AtTheEnd{}) noexcept
{ return interruptible<AtTheEnd>{}; }

/** Defines an ISR(Interrupt Service Routine)
    
    The parameter 'vector' is the name of an interrupt vector name
    used by the vector table. The variable argument can be use to put
    additional attributes.
 */
#define AVRINT_ISR(vector, ...) \
extern "C" \
[[gnu::signal, gnu::used, gnu::externally_visible, __VA_ARGS__]] void vector()

}}

#include "avr/interrupt/mcu.hpp"
