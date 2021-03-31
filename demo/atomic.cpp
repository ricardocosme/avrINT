#include <avr/interrupt.hpp>

using namespace avr::interrupt;

int main() {
    on();
    off();
    {
        atomic<> s;
        /** the code in this scope will be executed without being
            disturbed by interrupts. The interrups are enabled at the end
            of the scope only if they were enabled before. 

            [When using C++11]
            atomic<> s;
         */
    }
    {
        atomic<on_at_the_end_t> s;
        /** As above but interrupts are always enabled at the end of
            the scope.

            [When using C++11]
            atomic<on_at_the_end_t> s;
         */
    }
}
