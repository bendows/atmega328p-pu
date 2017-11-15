#include <avr/io.h>
#include <util/delay.h>
 
#define ON_DELAY_MS 30
#define OFF_DELAY_MS 1000
/* 
void flash (void) {
  PORTD = 0b01010101;
  _delay_ms(ON_DELAY_MS);
  PORTD = 0b10101010;
  _delay_ms(ON_DELAY_MS);
  PORTD = 0b00000000;
}

void delay_ms(uint16_t count) {
 while(count--) {
      _delay_ms(1);
      }
}

void delay_us(uint16_t count) {
while(count--) {
      _delay_us(1);
   }
}
*/
void main (void)
{
	char i=0;
 DDRD = 0b11111111;
 while(1) {
	 /*
	 for (PORTD = 0x01; PORTD != 0; PORTD <<= 1) 
		 _delay_ms(110);
		 */
	 PORTD = 0b01010101;
		 _delay_ms(1000);
	 for (PORTD = 0x80; PORTD != 0; PORTD >>= 1) 
		 _delay_ms(1000);
	 PORTD = 0b01010101;
		 _delay_ms(1000);
	 for (PORTD = 0x01; PORTD != 0; PORTD <<= 1) 
		 _delay_ms(1000);
	 /*
	 PORTD = 0b10101010;
		 _delay_ms(110);
	 PORTD = 0b01010101;
		 _delay_ms(110);
	 for (PORTD = 0x80; PORTD != 0; PORTD >>= 1) 
		 _delay_ms(110);
	 PORTD = 0b10101010;
		 _delay_ms(110);
	 PORTD = 0b01010101;
		 _delay_ms(110);
		 */
 }
}
