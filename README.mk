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

