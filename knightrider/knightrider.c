#include <avr/io.h>
#include <util/delay.h>

#define ON_DELAY_MS 30
#define OFF_DELAY_MS 1000
void main (void)
{
 DDRD = 0b11111111;
 while(1) {
         for (PORTD = 0x80; PORTD != 0; PORTD >>= 1)
                 _delay_ms(220);
         for (PORTD = 0x01; PORTD != 0; PORTD <<= 1)
                 _delay_ms(220);
         PORTD = 0x0;
                 _delay_ms(1000);
         PORTD = 255;
                 _delay_ms(1000);
         PORTD = 0;
                 _delay_ms(1000);
         PORTD = 0b01010101;
                 _delay_ms(1000);
         PORTD = 0b10101010;
                 _delay_ms(1000);
         for (PORTD = 0; PORTD < 255; PORTD++)
                 _delay_ms(120);
        _delay_ms(1000);
         PORTD = 0;
        _delay_ms(1000);
         PORTD = 255;
        _delay_ms(1000);
 }
}
