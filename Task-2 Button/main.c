/*
 * Button_Led.c
 *
 * Created: 9/23/2016 1:49:32 AM
 *  Author: rkasera
 */ 
 /*
 Fuse Bit : 
 Low Fuse  : E4
 High Fuse : D9
 
 Hz : 8MHz
 
 LED : Port C Bit 1 & 2
 Button : Port C Bit 0
 */
#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
int main(void)
{
	
	DDRC = 0xFE;
	PORTC = 0xFF;
	char a ;
    while(1)
    {
		 a = PINC & 0x01;
		
		if(!(a & 0x01))
		{
		   PORTC &= 0xf5;
		   _delay_ms(200);
		   PORTC |= 0x03;	
		}
         
    }
}