CC=avr-gcc
MCU?=atmega328p
F_CPU?=8000000
CFLAGS=-mmcu=$(MCU) -DF_CPU=$(F_CPU)UL -Os -w
FILENAME?=blink
TTYUSB?=ttyUSB0

.PHONY: print_vars

print_vars:
        avrdude -vvvV -c stk500v1 -p ATMEGA328P -P /dev/$(TTYUSB) -b 19200
        echo $(FILENAME)
        echo $(MCU)
        echo $(F_CPU)
        echo $(TTYUSB)
        echo $(CFLAGS)

default: $(FILENAME).hex

flash: default
        avrdude -vvV -c stk500v1 -p ATMEGA328P -P /dev/$(TTYUSB) -b 19200 -U flash:w:$(FILENAME).hex

%.o: %.c
        avr-gcc ${CFLAGS} -c -o $@ $<

%.out: %.o
        avr-gcc -mmcu=atmega328p $< -o $@

%.hex: %.out
        avr-objcopy -O ihex -R .eeprom $< $@

clean:
        rm -fv *.o *.hex

internalclock:
        avrdude -vvvV -c stk500v1 -p ATMEGA328P -P /dev/$(TTYUSB) -b 19200 -U lfuse:w:0xe2:m -U hfuse:w:0xd9:m -U efuse:w:0xff:m

16Mzclock:
        avrdude -vvvV -c stk500v1 -p ATMEGA328P -P /dev/$(TTYUSB) -b 19200 -U lfuse:w:0xff:m -U hfuse:w:0xde:m -U efuse:w:0xfd:m
