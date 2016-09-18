CC=avr-gcc
MCU=-mmcu=atmega328p 
CPU_SPEED?=8000000
CFLAGS=$(MCU) -DF_CPU=$(CPU_SPEED)UL -Os -w
.PHONY: default
default: lcd.hex

flash: default
	avrdude -V -c stk500v1 -p ATMEGA328P -P /dev/ttyUSB4 -b 19200 -U flash:w:lcd.hex

%.o: %.c
	avr-gcc ${CFLAGS} -c *.c

%.out: %.o
	avr-gcc -mmcu=atmega328p *.o -o $@

%.hex: %.out
	avr-objcopy -O ihex -R .eeprom $< $@

clean:
	rm -v *.o *.hex
