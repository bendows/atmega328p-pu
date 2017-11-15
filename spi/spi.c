#include <avr/io.h>
#include <avr/delay.h>

void SPI_masterInit(void)
{
	DDRB |= (1<<PB3)|(1<<PB5)|(1<<PB2); //set MOSI, SCK and SS as output
	//PORTB |= (1<<PB2); //set SS to high
	//enable master SPI at clock rate Fck/16
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}

uint8_t SPI_sendByte (uint8_t c)
{
	SPDR=c;
	while (!(SPSR &(1<<SPIF))); //wait for transmition complete
	return SPDR;
}

uint8_t SPI_receiveByte (void)
{
	return SPI_sendByte(0xFF);
}

int main(void)
{
	SPI_masterInit();
	//initial PWM value
	uint8_t pwmval = 0;
	PORTB |= (1<<PB2); //ss set to lo
	while (1)
	{
		PORTB |= ~(1<<PB2); //ss set to lo
		/*
		if (pwmval > 7)
			pwmval = 0;
			*/
		SPI_sendByte(pwmval++);
		PORTB |= (1<<PB2); //ss set to high
		_delay_ms(10);
	}
}
