#include <avr/interrupt.hpp>

using namespace avr;

int main() {
    interrupt::atomic sa{interrupt::restore};
    
    /** the code in this scope will be executed without being
     *  disturbed by interrupts. The interrupts are enabled again in
     *  the end of the scope if they were enabled before.
     */
}
