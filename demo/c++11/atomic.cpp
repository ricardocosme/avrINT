#include <avr/interrupt.hpp>

using namespace avr;

int main() {
    auto sa = interrupt::make_atomic();
    
    /** the code in this scope will be executed without being
     *  disturbed by interrupts. The interrups are enabled at the end
     *  of the scope. Take a look at 'atomic_restore.cpp' to see a
     *  solution that restore the state before the usage of the atomic
     *  in the end of the scope.
     */
}
