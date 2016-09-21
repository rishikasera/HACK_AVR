
#include<avr/io.h>
#define F_CPU 8000000UL
#include<util/delay.h>
#include "lcd4bit.h"

/*==============================================================================*/
/*                         Main  Function Defination                            */
/*==============================================================================*/

int main()
{
    DDRC = 0xFF;
	PORTC = 0xFF;
	
	Init_Ports();
    Init_LCD();
    Print_String("$ DigitalWorld $");
	gotoXy(0,1);
    Print_String(" * WelcomeYOU * ");
    
	
	
	while(1){
		PORTC = 0xFF;
		_delay_ms(1000);
		PORTC = 0x00;
		_delay_ms(1000);	
	}    
	
}
