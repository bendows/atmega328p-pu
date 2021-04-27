#include <avr/io.h>
#include <util/delay.h>
 
void main (void) {
 DDRD = 0b11111111;
 while(1) {
  PORTB = 0b00000000;
  delay_ms(700);
  PORTB = 0b11111111;
  delay_ms(200);
 }
}
