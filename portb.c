#include <avr/io.h>
#include <util/delay.h>
 
char digits[] = { 0xbb, 0x21, 0xea, 0xe3, 0x71, 0xd3, 0xdb, 0x23, 0xfb, 0xf3 }; 

void display_number(int n) {

	 for (unsigned int i = 0; i<20;i++) {
		PORTD &= ~((1 << PIND6)|(1 << PIND7));
  		unsigned int one = (n % 10); 
  		unsigned int tens = ((n / 10) % 10); 
  		PORTD |= (1 << PIND6); PORTB = digits[one]; _delay_ms(10);
		PORTD &= ~((1 << PIND6)|(1 << PIND7));
  		PORTD |= (1 << PIND7); PORTB = digits[tens]; _delay_ms(10);
	}
}

int main (void) {

 DDRB = 0b11111111;
 DDRD = 0b11111111;

 /*
 DDRD |= (1<< PIND6);
 DDRD |= (1<< PIND7);
 */

 while(1) {
	 for (unsigned int i = 0; i<100;i++) {
		 display_number(i);
	 }
 }
 return 0;
}
