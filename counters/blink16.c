#include <avr/io.h>
#include <avr/interrupt.h>

int extraTime = 0;

int main(void)
{
	DDRB = 0x01; //SET PIN TO OUT
	TCCR1B = (1 << WGM12); //SET TIMER MODE TO CTC MODE/BIT
	OCR1A = 156; 
	TIMSK1 = (1 << OCIE1A); 

	sei();  //SET EXTERNAL INTERRUPT

	TCCR1B |= (1 << CS12) | ( 1 << CS10); //SET PRESCALER 1024

    	while(1)
    	{
        // do nothing
        // whenever a match occurs, ISR is fired
        // toggle the led in the ISR itself
        // no need to keep track of any flag bits here
        // done!
    	}
}

ISR(TIMER1_COMPA_vect)
{
    extraTime++;
    // toggle led here
    if (extraTime > 100) {
        extraTime = 0;
    	PORTB ^= (1 << PORTB0);	//TOGGLE PB0 
	}
}
