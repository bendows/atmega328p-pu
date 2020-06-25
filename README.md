# Flashing avr-gcc binaries to a standalone atmega328p-pu with an Arduino Nano

## Make the Arduino Nano a programmer
function as a programmer burn the "ArduinoISP" sketch under "file"->"examples"->"ArduinoISP" in the Arduino IDE to it.
If you are using the Arduino 1.0 (or later) IDE you need to change the delay value of the heartbeat:
Find:
```bash
//
// this provides a heartbeat on pin 9, so you can tell the software is running.
uint8_t hbval=128;
int8_t hbdelta=8;
void heartbeat() {
if (hbval > 192) hbdelta = -hbdelta;
if (hbval < 32) hbdelta = -hbdelta;
hbval += hbdelta;
analogWrite(LED_HB, hbval);
delay(40);
}
//
and change the delay(40) to delay(20).
```
# Then compile and upload the sketch using the Ardiuno IDE.

Install software (Ubuntu)
```bash
apt-get install avrdude gcc-avr avr-libc
```

Install software (ArcoLinuxB-openbox)
```bash
pacman -S avr-gcc
pacman -S avrdude
```

# Many thanks to these good resources:

http://www.martyncurrey.com/arduino-on-a-breadboard/

http://www.martyncurrey.com/arduino-nano-as-an-isp-programmer/

https://github.com/nickgammon/arduino_sketches

http://www.gammon.com.au/forum/?id=11635#

```txt
# Configure the atmega328p fuze bits for selecting it's internal 8MHz clock
sudo make 8MHzclock

# Configure the atmega328p fuze bits for selecting an external 16MHz clock
sudo make 16MHzclock

# Configure the atmega328p fuze bits for selecting it's clock and compile and flash main.c afterwards

sudo FILENAME=main F_CPU=8000000 make 8MHzclock flash
sudo FILENAME=main F_CPU=16000000 make 16MHzclock flash

# Just compile and flash main.c

sudo FILENAME=main F_CPU=16000000 make 16MHzclock flash
sudo FILENAME=main F_CPU=16000000 make 8MHzclock flash
```

```txt
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
```
# Using the Arduino Nano as an ISP programmer (running the stk500v1 ISP scetch) to program a standalone Atemga328p pu.
```txt
standalone Atmega328p-pu <<->> Arduino Nano connections

	standalone Atmega328p-pu connections and connections to Nano

If the fuses on the standalone Atmega328p-pu is set for using the internal 8MHz clock 
you dont need to connect an external crystal

If the fuses on the Atmega328p-pu is set for using an external clock, connect an external 16MHz crystal to pins 9 and 10 
of the standalone Atmega328p-pu. I did not need to connect two 22pF caps from pin 9 to GND and from PIN 10 to GND 
respectively, but it's probably a good idea
```
# Arduino Nano connections

```txt

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
```

The Arduino Nano is connected to the computer via a USB to MINI USB cable which also supplies VCC to the Nano.
The VCC of the Nano (+4.8V in this case) is made available externaly on the '+5V' pin of the Nano which is used to supply VCC to the 
standalone Atmega328p-pu chip as well. The '+5V' pin of the Nano is the 4th pin, when counting from the Nano\'s VIN pin on 
the same side of the Nano and must be connected to VCC so that the Atemga328p-pu gets power.
Therefore, the standalone Atmega328p-pu chip\'s GND bus must be connected to any of the 2 GND pins of the the Arduino Nano.
For Nano clones I had to connect a 10uF electrolytic cap between any of the 2 RST and GND pairs on the Arduino Nano
On my Nano clone A0-A7 was labeled in reverse
```txt
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
```

On the NANO maybe need a 10Uf electrolytic between reset and GND on the VIN pins side

```txt
# dmesg -T

[Thu Sep 12 22:57:40 2019] usb 3-1: USB disconnect, device number 8
[Thu Sep 12 22:57:40 2019] ftdi_sio ttyUSB0: FTDI USB Serial Device converter now disconnected from ttyUSB0
[Thu Sep 12 22:57:40 2019] ftdi_sio 3-1:1.0: device disconnected
[Thu Sep 12 22:57:42 2019] usb 3-1: new full-speed USB device number 9 using xhci_hcd
[Thu Sep 12 22:57:42 2019] usb 3-1: New USB device found, idVendor=0403, idProduct=6001
[Thu Sep 12 22:57:42 2019] usb 3-1: New USB device strings: Mfr=1, Product=2, SerialNumber=3
[Thu Sep 12 22:57:42 2019] usb 3-1: Product: FT232R USB UART
[Thu Sep 12 22:57:42 2019] usb 3-1: Manufacturer: FTDI
[Thu Sep 12 22:57:42 2019] usb 3-1: SerialNumber: A7030WNQ
[Thu Sep 12 22:57:42 2019] ftdi_sio 3-1:1.0: FTDI USB Serial Device converter detected
[Thu Sep 12 22:57:42 2019] usb 3-1: Detected FT232RL
[Thu Sep 12 22:57:42 2019] usb 3-1: FTDI USB Serial Device converter now attached to ttyUSB0

# avrdude -vvvV -c stk500v1 -p ATMEGA328P -P /dev/ttyUSB0 -b 19200

avrdude: Version 6.2
         Copyright (c) 2000-2005 Brian Dean, http://www.bdmicro.com/
         Copyright (c) 2007-2014 Joerg Wunsch

         System wide configuration file is "/etc/avrdude.conf"
         User configuration file is "/root/.avrduderc"
         User configuration file does not exist or is not a regular file, skipping

         Using Port                    : /dev/ttyUSB0
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
                                  Block Poll               Page                       Polled
           Memory Type Mode Delay Size  Indx Paged  Size   Size #Pages MinW  MaxW   ReadBack
           ----------- ---- ----- ----- ---- ------ ------ ---- ------ ----- ----- ---------
           flash         65     6   128    0 yes     32768  128    256  4500  4500 0xff 0xff
                                  Block Poll               Page                       Polled
           Memory Type Mode Delay Size  Indx Paged  Size   Size #Pages MinW  MaxW   ReadBack
           ----------- ---- ----- ----- ---- ------ ------ ---- ------ ----- ----- ---------
           lfuse          0     0     0    0 no          1    0      0  4500  4500 0x00 0x00
                                  Block Poll               Page                       Polled
           Memory Type Mode Delay Size  Indx Paged  Size   Size #Pages MinW  MaxW   ReadBack
           ----------- ---- ----- ----- ---- ------ ------ ---- ------ ----- ----- ---------
           hfuse          0     0     0    0 no          1    0      0  4500  4500 0x00 0x00
                                  Block Poll               Page                       Polled
           Memory Type Mode Delay Size  Indx Paged  Size   Size #Pages MinW  MaxW   ReadBack
           ----------- ---- ----- ----- ---- ------ ------ ---- ------ ----- ----- ---------
           efuse          0     0     0    0 no          1    0      0  4500  4500 0x00 0x00
                                  Block Poll               Page                       Polled
           Memory Type Mode Delay Size  Indx Paged  Size   Size #Pages MinW  MaxW   ReadBack
           ----------- ---- ----- ----- ---- ------ ------ ---- ------ ----- ----- ---------
           lock           0     0     0    0 no          1    0      0  4500  4500 0x00 0x00
                                  Block Poll               Page                       Polled
           Memory Type Mode Delay Size  Indx Paged  Size   Size #Pages MinW  MaxW   ReadBack
           ----------- ---- ----- ----- ---- ------ ------ ---- ------ ----- ----- ---------
           calibration    0     0     0    0 no          1    0      0     0     0 0x00 0x00
                                  Block Poll               Page                       Polled
           Memory Type Mode Delay Size  Indx Paged  Size   Size #Pages MinW  MaxW   ReadBack
           ----------- ---- ----- ----- ---- ------ ------ ---- ------ ----- ----- ---------
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
avrdude: safemode read 1, lfuse value: e2
avrdude: safemode read 2, lfuse value: e2
avrdude: safemode read 3, lfuse value: e2
avrdude: safemode: lfuse reads as E2
avrdude: safemode read 1, hfuse value: d9
avrdude: safemode read 2, hfuse value: d9
avrdude: safemode read 3, hfuse value: d9
avrdude: safemode: hfuse reads as D9
avrdude: safemode read 1, efuse value: ff
avrdude: safemode read 2, efuse value: ff
avrdude: safemode read 3, efuse value: ff
avrdude: safemode: efuse reads as FF

avrdude: safemode read 1, lfuse value: e2
avrdude: safemode read 2, lfuse value: e2
avrdude: safemode read 3, lfuse value: e2
avrdude: safemode: lfuse reads as E2
avrdude: safemode read 1, hfuse value: d9
avrdude: safemode read 2, hfuse value: d9
avrdude: safemode read 3, hfuse value: d9
avrdude: safemode: hfuse reads as D9
avrdude: safemode read 1, efuse value: ff
avrdude: safemode read 2, efuse value: ff
avrdude: safemode read 3, efuse value: ff
avrdude: safemode: efuse reads as FF
avrdude: safemode: Fuses OK (E:FF, H:D9, L:E2)

avrdude done.  Thank you.

Example make output:


# pwd
# /home/ben
YELLOW
# avrdude -V -c stk500v1 -p ATMEGA328P -P /dev/ttyUSB0 -b 19200
# avrdude -V -c stk500v1 -p ATMEGA328P -P /dev/ttyUSB0 -b 19200
avrdude: ser_open(): can't open device "/dev/ttyUSB0": Permission denied
avrdude done.  Thank you.
# sudo su
[sudo] password for ben:
# avrdude -V -c stk500v1 -p ATMEGA328P -P /dev/ttyUSB0 -b 19200

avrdude: AVR device initialized and ready to accept instructions

Reading | ################################################## | 100% 0.05s

avrdude: Device signature = 0x1e950f (probably m328p)

avrdude: safemode: Fuses OK (E:FF, H:D9, L:E2)

avrdude done.  Thank you.

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
# ABOVE IS WITH INTERNAL 8MHz 
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
```
