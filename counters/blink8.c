#include <avr/io.h>
#include <avr/interrupt.h>

int extraTime = 0;
int i = 5;

int main(void)
{
	DDRB = 0x01; //SET PIN TO OUT
	TCCR0A = (1 << WGM01); //SET TIMER MODE TO CTC MODE/BIT
	OCR0A = 156; 
	TIMSK0 = (1 << OCIE0A); 
	TCCR0B = (1 << CS02) | (1<<CS00); //SET PRESCALER 1024

	sei();  //SET EXTERNAL INTERRUPT

	TCCR0B = (1 << CS02) | ( 1 << CS00);	//START AT 1024 PRESCALAR

    	while(1)
    	{
        // do nothing
        // whenever a match occurs, ISR is fired
        // toggle the led in the ISR itself
        // no need to keep track of any flag bits here
        // done!
    	}
}

ISR(TIMER0_COMPA_vect)
{
    extraTime++;
    // toggle led here
    if (extraTime > 100*i) {
        extraTime = 0;
    	PORTB ^= (1 << PORTB0);	//TOGGLE PB0 
    }
}
