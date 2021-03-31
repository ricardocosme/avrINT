#include <avr/interrupt.hpp>

using namespace avr::interrupt;

int main() {
    on();
    off();
    {
        interruptible s;
        /** the code in this scope will be executed with interrupts
            turned on. The interrupions are disabled at the end of the
            scope only if they were disabled before.

            [When using C++11]
            interruptible<> s;
         */
    }
    {
        interruptible s{off_at_the_end};
        /** As above but interrupts are always disabled at the end of
            the scope.

            [When using C++11]
            interruptible<off_at_the_end_t> s;
         */
    }
}
