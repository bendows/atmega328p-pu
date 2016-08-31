CC=avr-gcc
MCU=-mmcu=atmega328p 
CPU_SPEED=-DF_CPU=16000000UL
CFLAGS=$(MCU) $(CPU_SPEED) -Os -w
# Can other things "flash"? Or be "flashed"? The word has several definitions.
.PHONY: default
default: knightrider.hex

flash: default
	avrdude -V -c stk500v1 -p ATMEGA328P -P /dev/ttyUSB0 -b 19200 -U flash:w:knightrider.hex

%.o: %.c
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o $@ $<

%.out: %.o
	avr-gcc -mmcu=atmega328p $< -o $@

%.hex: %.out
	avr-objcopy -O ihex -R .eeprom $< $@

clean:
	rm -v *.hex
