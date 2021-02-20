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

/** Tag to be used as a parameter to the constructor of the class
 * 'atomic'. It informs that the status register state should be
 * recovered in the end of the atomic scope. */
struct restore_t{};

namespace detail{
struct no_restore_t{};
} //namespace detail

/** RAII to execute code without being disturbed by interrupts 
    
    By default the global interrupts are enabled in the end of the
    scope, but if the parameter 'restore' is passed to the constructor
    then the status register state that was before the atomic scope is
    recovered, which means that the global interrupts is enabled only
    if they were enabled before.

    Example:

      {
        atomic sa;
        //my code
      }
   
      {
        atomic sa(restore);
        //my code
      }
*/
template<typename Restore = detail::no_restore_t>
class atomic {
    uint8_t _sreg;
public:
    constexpr static bool is_restore
        {detail::is_same<Restore, restore_t>::value};
    
    explicit atomic(Restore = Restore{}) noexcept {
        if(is_restore) _sreg = io::sreg;
        off();
    }
    
    ~atomic() noexcept {
        if(is_restore) io::sreg = _sreg;
        else on();
    }
};

#if __cplusplus >= 201703L
inline constexpr restore_t restore;
#else
namespace {
constexpr auto& restore{detail::global<restore_t>::instance};
}//anonymous namespace
#endif

/** [C++11/14] The atomic ctor should be use if C++17 is available. */
template<typename Restore = detail::no_restore_t>
[[gnu::always_inline, nodiscard]]
inline atomic<Restore> make_atomic(Restore = Restore{}) noexcept
{ return atomic<Restore>{}; }

/** Defines an ISR(Interrupt Service Routine)
    
    The parameter 'vector' is the name of an interrupt vector name
    used by the vector table. The variable argument can be use to put
    additional attributes.
 */
#define AVRINT_ISR(vector, ...) \
extern "C" \
[[gnu::signal, gnu::used, gnu::externally_visible, __VA_ARGS__]] void vector()

}}
