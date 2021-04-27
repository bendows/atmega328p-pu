#include <avr/io.h>
#include <util/delay.h>
 
char digits[] = { 0xbb, 0x21, 0xea, 0xe3, 0x71, 0xd3, 0xdb, 0x23, 0xff, 0xf7 }; 
int main (void) {
 DDRB = 0b11111111;
 while(1) {
	 for (unsigned int i = 0; i<10;i++) {
  		PORTB = digits[i]; _delay_ms(1000);
	 }
 }
 return 0;
}
