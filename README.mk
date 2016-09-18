# STANDOLINE ATMEGA328P-PU

VCC = +5V

VCC - R 10k   -	1	28
		2	27
		3	26
		4	25
		5	24
		6	23
VCC  - 		7	22   	- 	GND
GND  -		8	21	-	VCC
GND  - C 22pF -	9	20	-	VCC
GND  - C 22pF -	10	19
		11	18
		12	17
		13	16
		14	15


stk500v1 isp connections

standalone 				isp

1		-			D10
17		-			D11
18		-			D12
19		-			D13

Example make output:

make flash CPU_SPEED=8000000

avr-gcc -mmcu=atmega328p  -DF_CPU=8000000UL -Os -w -c -o knightrider.o knightrider.c
avr-gcc -mmcu=atmega328p knightrider.o -o knightrider.out
avr-objcopy -O ihex -R .eeprom knightrider.out knightrider.hex
avrdude -V -c stk500v1 -p ATMEGA328P -P /dev/ttyUSB4 -b 19200 -U flash:w:knightrider.hex

avrdude: AVR device initialized and ready to accept instructions

Reading | ################################################## | 100% 0.05s

avrdude: Device signature = 0x1e950f (probably m328p)
avrdude: NOTE: "flash" memory has been specified, an erase cycle will be performed
         To disable this feature, specify the -D option.
avrdude: erasing chip
avrdude: reading input file "knightrider.hex"
avrdude: input file knightrider.hex auto detected as Intel Hex
avrdude: writing flash (208 bytes):

Writing | ################################################## | 100% 0.31s

avrdude: 208 bytes of flash written

avrdude: safemode: Fuses OK (E:FF, H:D9, L:E2)

avrdude done.  Thank you.

rm knightrider.o knightrider.out
# avr-projects]$ 
