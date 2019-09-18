# use 8Mz internal clock
avrdude -vvvV -c stk500v1 -p ATMEGA328P -P /dev/ttyUSB0 -b 19200 -U lfuse:w:0xe2:m -U hfuse:w:0xd9:m -U efuse:w:0xff:m
# use external 16 Mgz crystal
avrdude -vvvV -c stk500v1 -p ATMEGA328P -P /dev/ttyUSB0 -b 19200 -U lfuse:w:0xff:m -U hfuse:w:0xde:m -U efuse:w:0xfd:m
