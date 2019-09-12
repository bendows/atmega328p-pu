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

Using an Arduino Nano as an ISP programmer (running the stk500v1 ISP scetch) to program a standalone Atemga328p-pu chip.

standalone Atmega328p-pu <<->> Arduino Nano connections

	standalone Atmega328p-pu connections and connections to Nano

If the fuses on the Atmega328p-pu is set for using the internal 8Mz clock you dont need to connect an external crystal to the Atmega328p-pu
If the fuses on the Atmega328p-pu is set for using an external clock, connect an external 16Mz crystal to pins 9 and 10 on the atmega328p-pu standalone chip
I did not need to connect two 22pF caps from pin 9 to GND and from PIN 10 to GND respectively.

	D10    	1	28
		2	27
		3	26
		4	25
		5	24
		6	23
VCC   		7	22  	GND
GND  		8	21	VCC
		9	20	VCC
    		10	19	D13
		11	18	D12
		12	17	D11
		13	16
		14	15

	Arduino Nano connections

The Arduino Nano is connected to the computer via a USB to MINI USB cable which also supplies VCC to the Nano.
The VCC of the Nano (+4.8V in this case) is made available externaly on the '+5V' pin of the Nano which is used to supply VCC to the standalone Atmega328p-pu chip as well.
The '+5V' pin of the Nano is the 4th pin, when counting from the Nano\'s VIN pin on the same side of the Nano and must be connected to VCC so that the Atemga328p-pu gets power.
Therefore, the standalone Atmega328p-pu chip\'s GND bus must be connected to any of the 2 GND pins of the the Arduino Nano.
For Nano clones I had to connect a 10uF electrolytic cap between any of the 2 RST and GND pairs on the Arduino Nano
On my Nano clone A0-A7 was labeled in reverse

	MINI USB CONNECTOR HERE

	    	D13	D12	
		3v3	D11
		AREF	D10
		A0	D9	<-- orange LED 	--> GND (heartbeat)
		A1	D8	<-- red LED 	--> GND (bad IO activity)
		A2	D7	<-- green LED 	--> GND (good IO activity)
		A3	D6
		A4	D5	
		A5	D4
		A6	D3
		A7	D2
VCC  <--	+5V	GND		GND
		RST	RST
GND 		GND	RX0	
 		VIN	TX1

	ICSP HEADER HERE

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
#
#
# ABOVE IS WITH INTERNAL 8Mz 
#
# BELOW IS WITH 16mZ EXTERNAL CRYSTAL
#

avrdude: Version 6.3, compiled on Feb 21 2016 at 13:33:25
         Copyright (c) 2000-2005 Brian Dean, http://www.bdmicro.com/
         Copyright (c) 2007-2014 Joerg Wunsch

         System wide configuration file is "/etc/avrdude.conf"
         User configuration file is "/home/ben/.avrduderc"
         User configuration file does not exist or is not a regular file, skipping

         Using Port                    : /dev/ttyUSB4
         Using Programmer              : stk500v1
         Overriding Baud Rate          : 19200
         AVR Part                      : ATmega328P
         Chip Erase delay              : 9000 us
         PAGEL                         : PD7
         BS2                           : PC2
         RESET disposition             : dedicated
         RETRY pulse                   : SCK
         serial program mode           : yes
         parallel program mode         : yes
         Timeout                       : 200
         StabDelay                     : 100
         CmdexeDelay                   : 25
         SyncLoops                     : 32
         ByteDelay                     : 0
         PollIndex                     : 3
         PollValue                     : 0x53
         Memory Detail                 :

                                  Block Poll               Page                       Polled
           Memory Type Mode Delay Size  Indx Paged  Size   Size #Pages MinW  MaxW   ReadBack
           ----------- ---- ----- ----- ---- ------ ------ ---- ------ ----- ----- ---------
           eeprom        65    20     4    0 no       1024    4      0  3600  3600 0xff 0xff
           flash         65     6   128    0 yes     32768  128    256  4500  4500 0xff 0xff
           lfuse          0     0     0    0 no          1    0      0  4500  4500 0x00 0x00
           hfuse          0     0     0    0 no          1    0      0  4500  4500 0x00 0x00
           efuse          0     0     0    0 no          1    0      0  4500  4500 0x00 0x00
           lock           0     0     0    0 no          1    0      0  4500  4500 0x00 0x00
           calibration    0     0     0    0 no          1    0      0     0     0 0x00 0x00
           signature      0     0     0    0 no          3    0      0     0     0 0x00 0x00

         Programmer Type : STK500
         Description     : Atmel STK500 Version 1.x firmware
         Hardware Version: 2
         Firmware Version: 1.18
         Topcard         : Unknown
         Vtarget         : 0.0 V
         Varef           : 0.0 V
         Oscillator      : Off
         SCK period      : 0.1 us

avrdude: AVR device initialized and ready to accept instructions

Reading | ################################################## | 100% 0.05s

avrdude: Device signature = 0x1e950f (probably m328p)
avrdude: safemode: hfuse reads as DF
avrdude: safemode: efuse reads as FD

avrdude: safemode: hfuse reads as DF
avrdude: safemode: efuse reads as FD
avrdude: safemode: Fuses OK (E:FD, H:DF, L:FF)

avrdude done.  Thank you.

