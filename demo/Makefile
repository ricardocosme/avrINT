mcu=attiny13a
std=c++17

all: atomic.elf interruptible.elf isr.elf on_off.elf

%.elf: %.cpp
	avr-g++ -Wall -Os -std=$(std) -mmcu=$(mcu) -I../include -o $@ $<
	avr-size $@

%.s: %.elf
	avr-objdump -d $< > $@
	cat $@

.PHONY: clean

clean:
	rm -f *.elf *.s
