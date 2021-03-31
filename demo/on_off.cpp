#include <avr/interrupt.hpp>

using namespace avr;

int main() {
    interrupt::on();
    interrupt::off();
}
