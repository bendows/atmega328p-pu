#include <avr/io.h>
#include <avr/delay.h>

//SPI master
#include <avr/io.h>
#include <util/delay.h>
//SPI init
void SPIMasterInit(void)
{
//set MOSI, SCK and SS as output
DDRB |= (1<<PB3)|(1<<PB5)|(1<<PB2);
//set SS to high
//PORTB |= (1<<PB2); //BEN ??
//enable master SPI at clock rate Fck/16
SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}
//master send function
uint8_t SPIMasterSend (uint8_t c)
{
//send data
SPDR=c;
//wait for transmition complete
while (!(SPSR &(1<<SPIF)));
return SPDR;
}
int main(void)
{
//initialize master SPI
SPIMasterInit();
//initial PWM value
uint8_t pwmval = 0;
while (1)
{
//select slave
PORTB &= ~(1<<PB2); //BEN ??
SPIMasterSend(pwmval++);
//SS to high
PORTB |= (1<<PB2); //BEN ??
_delay_ms(10);
}
}

