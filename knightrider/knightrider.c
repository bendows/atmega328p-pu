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
	 for (PORTD = 0x01; PORTD != 0; PORTD <<= 1) 
		 _delay_ms(200);
	 for (PORTD = 0x80; PORTD != 0; PORTD >>= 1) 
		 _delay_ms(200);
	 for (PORTD = 0x01; PORTD != 0; PORTD <<= 1) 
		 _delay_ms(200);
	 for (PORTD = 0x80; PORTD != 0; PORTD >>= 1) 
		 _delay_ms(200);
	 if (i>3) {
		i=0;
		continue;
	}
	 i++;
	 PORTD = 0x11;
		 _delay_ms(100);
	 PORTD = 0x22;
		 _delay_ms(100);
	 PORTD = 0x33;
		 _delay_ms(100);
	 PORTD = 0x44;
		 _delay_ms(100);
	 PORTD = 0x55;
		 _delay_ms(100);
	 PORTD = 0x66;
		 _delay_ms(100);
	 PORTD = 0x77;
		 _delay_ms(100);
	 PORTD = 0x88;
		 _delay_ms(400);
 }
}
