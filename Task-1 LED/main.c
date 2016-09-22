/*
 * LED_ON.c
 *
 * Created: 9/23/2016 1:44:05 AM
 *  Author: rkasera
 */ 


#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
int main(void)
{
	
	DDRC = 0xFF;
	PORTC = 0xFF;
    while(1)
    {
        PORTC = 0xFF;
		_delay_ms(1000);
		PORTC = 0x00;
		_delay_ms(1000); 
    }
}