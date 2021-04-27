#include <avr/io.h>
#include <util/delay.h>
 
char digits[] = { 0xbb, 0x21, 0xea, 0xe3, 0x71, 0xd3, 0xdb, 0x23, 0xfb, 0xf3 }; 
int main (void) {

 DDRB = 0b11111111;
 DDRD = 0b11111111;

 /*
 DDRD |= (1<< PIND6);
 DDRD |= (1<< PIND7);
 */

 while(1) {
	 for (unsigned int i = 0; i<10;i++) {
		PORTD &= ~((1 << PIND6)|(1 << PIND7));
		if (i ==4) {
  			PORTD |= (1 << PIND6);
		}
		if (i ==5) {
  			PORTD |= (1 << PIND7);
		}
  		PORTB = digits[i]; 
  		//PORTB = digits[(i % 10)]; 
		_delay_ms(1000);
	 }
 }
 return 0;
}
