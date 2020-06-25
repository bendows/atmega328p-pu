#include <avr/io.h>
#include <util/delay.h>
 
#define ON_DELAY_MS 30
#define OFF_DELAY_MS 1000
 
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

void main (void)
{
unsigned int i=5;
 DDRD = 0b11111111;
 while(1) {

	 while (1) {
 if (i >= 300) { 
	 break;
	}
   flash();
  delay_ms(i);
  i+=5;
}
	 while (1) {
 if (i <= 5) { 
	 break;
	}
   flash();
  delay_ms(i);
  i-=5;
}
 }
}
