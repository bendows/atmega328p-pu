#include <avr/io.h>
#include <util/delay.h>
 
#define ON_DELAY_MS 30
#define OFF_DELAY_MS 1000

const int d[10] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F };
unsigned int i=0;

void pint (unsigned int i) {
		int ones = i%10;
		int tens = (i != 0) ? i/10 : 0;
		PORTD = d[tens];
		PORTB = ( 1<< PB6);
		 _delay_ms(10);
		PORTD = d[ones];
		PORTB = ( 1<< PB7);
		 _delay_ms(10);
}
void main (void) {
 	DDRD = 0b11111111;
 	DDRB = 0b11111111;
	while(1) {

		PORTB = (1<<PB7 | 1<< PB6);
        for (PORTD = 1; PORTD !=0; PORTD <<= 1) {     //KnightRider
                 _delay_ms(500);
	}
        PORTD = 128; _delay_ms(5000);	//The period
//	PORTB = 0;
	for (i=0;i<100;i++) { 		//Count from 0 to 99
		pint (i);
	}
	for (i=99;i>0;i--) { 		//Count from 0 to 99
		pint (i);
	}
 }
}
