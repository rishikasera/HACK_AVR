/*
 * ExInterrupt.c
 *
 * Created: 9/24/2016 3:32:51 AM
 *  Author: rkasera
 */ 


#include <avr/io.h>
#define F_CPU 8000000UL
#include <avr/interrupt.h>
#include <util/delay.h>


#define DataPort	PORTC	// Using PortC as our Dataport
#define DataDDR		DDRC

//Interrupt Service Routine for INT0
ISR(INT0_vect)
{
	
		DataPort = 0x00;
		_delay_ms(500);	// Wait 5 seconds
		DataPort = 0xFF;
		_delay_ms(500);	// Wait 5 seconds
		DataPort = 0x00;
		_delay_ms(500);	// Wait 5 seconds
		DataPort = 0xFF;
		_delay_ms(500);
	
}

int main(void)
{
	DDRD = 1<<PD2;		// Set PD2 as input (Using for interupt INT0)
	PORTD = 1<<PD2;		// Enable PD2 pull-up resistor
	
	DataDDR = 0xFF;		// Configure Dataport as output
	DataPort = 0x01;	// Initialise Dataport to 1
	
	GICR = 1<<INT0;					// Enable INT0
	MCUCR = 1<<ISC01 | 1<<ISC00;	// Trigger INT0 on rising edge
	
	sei();				//Enable Global Interrupt
	
	while(1)
	{
		
         PORTC = 0xfe;
		 _delay_ms(500);
		 PORTC = 0x01;
		 _delay_ms(500);		
		
		
	}
}





