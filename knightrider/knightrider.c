#include <avr/io.h>
#include <util/delay.h>
 
#define ON_DELAY_MS 30
#define OFF_DELAY_MS 1000

	unsigned char i=0;
void main (void) {
 	DDRD = 0b11111111;
	while(1) {
	for (PORTD = 0x1; PORTD != 0; PORTD <<= 1) 	//KnightRider
		 _delay_ms(150);
	 for (PORTD = 0x80; PORTD != 0; PORTD >>= 1) 	//KnightRider
		 _delay_ms(150);

	//DOUBLE FLASH
	PORTD = 0; _delay_ms(250); PORTD = 0b10101010; _delay_ms(150);
	PORTD = 0; _delay_ms(250); PORTD = 0b10101010; _delay_ms(150);
	PORTD = 0; _delay_ms(250);

	for (PORTD = 1; PORTD != 0; PORTD <<= 1) 	//KnightRider
		 _delay_ms(150);
	 for (PORTD = 128; PORTD != 0; PORTD >>= 1) 	//KnightRider
		 _delay_ms(150);
	//DOUBLE FLASH
	PORTD = 0; _delay_ms(250); PORTD = 0b10101010; _delay_ms(150);
	PORTD = 0; _delay_ms(250); PORTD = 0b10101010; _delay_ms(150);
	PORTD = 0; _delay_ms(250);
	for (PORTD=0;PORTD<255;PORTD++) { 		//Count from 0 to 255
		 _delay_ms(50);
	}
 }
}
