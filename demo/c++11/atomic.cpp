#include <avr/interrupt.hpp>

using namespace avr;

int main() {
    {
        auto s = interrupt::make_atomic();
        /** the code in this scope will be executed without being
         *  disturbed by interrupts. The interrups are enabled at the end
         *  of the scope only if they were enabled before. 
         */
    }

    {
        auto s = interrupt::make_atomic(interrupt::on_at_the_end);
        /** As above but interrupts are always enabled at the end of
         *  the scope.
         */
    }
}
