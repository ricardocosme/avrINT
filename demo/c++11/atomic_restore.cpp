#include <avr/interrupt.hpp>

using namespace avr;

int main() {
    auto sa = interrupt::make_atomic(interrupt::restore);
    
    /** the code in this scope will be executed without being
     *  disturbed by interrupts. The interrupts are enabled again in
     *  the end of the scope if they were enabled before.
     */
}
