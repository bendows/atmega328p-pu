#include <avr/io.h>
#include <util/delay.h>
 
#define ON_DELAY_MS 30
#define OFF_DELAY_MS 1000
/*
PORTD = 0b10101010;
_delay_ms(ON_DELAY_MS);
PORTD = 0b00000000;
*/
void main (void)
{
 DDRD = 0b11111111;
 while(1) {
	 PORTD = 0b11010101;
		 _delay_ms(300);
	 PORTD = 0b11111011;
		 _delay_ms(300);
	 PORTD = 0b00010100;
		 _delay_ms(300);
	 PORTD = 0b00101111;
		 _delay_ms(300);
 }
}
