#include <avr/io.h>
#include <avr/interrupt.h>
int s = 0;
int m = 0;

ISR(TIMER1_COMPA_vect)
{
	s++;
	if (s>59)
	{
		m++;
		if (PINB & (1 << PB1))
		{
			PORTB &= ~(1 << PB1);
		}
		else
		{
			PORTB |= (1 << PB1);
		}
		s=0;
	}
	if (PINB & (1 << PB0))
	{
		PORTB &= ~(1 << PB0);
	}
	else
	{
		PORTB |= (1 << PB0);
	}
	TCNT1L = 0;
}

int main(void)
{
	DDRB = (1 << PB1)|(1 << PB0);
	PORTB = 0x00;
	TCCR1A = 0x40;
	TCCR1B = 0x05;
	OCR1AH = 0x3D;
	OCR1AL = 0x09;
	TIMSK = 0x10;
	sei();
    while(1);
}