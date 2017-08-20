
#include<avr/io.h>
#define F_CPU 1000000UL
#include<util/delay.h>

#include "lcd4bit.h"

char ss = 0;
char mm = 0;
char hh = 0;

void PrintLcd(char h,char m,char s);
void Init();
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
    
	_delay_ms(1000);
	_delay_ms(1000);
	_delay_ms(1000);
	
	while(1){
		
		_delay_ms(900);
		ss++;
		
		if(ss >= 60)
		{
			ss = 0;
			mm++;
			if(mm >= 60)
			{
				mm = 0;
				hh++;
				if(hh>=24)
				{
					hh=0;
				}
				
			}
		}
		PrintLcd(hh,mm,ss);	
	}    
	
}



void Init()
{
	
	Write_Command(0x01);
	_delay_us(10);
	Write_Command(0x02);
	_delay_us(10);
	Write_Command(0x0c);
	_delay_us(10);
}

void PrintLcd(char h,char m,char s)
{
	Init();
	
	char a = h % 10;
	char b = h / 10;
	char c = m % 10;
	char d = m /10;
	char e = s % 10;
	char f = s / 10;
	
	
   	Write_data(' ');
   	Write_data(' ');
	Write_data(' ');
	Write_data(' ');   
	
	
	
	Write_data(b+48);
	Write_data(a+48);
	_delay_us(10);
	Write_data(':');
	Write_data(d+48);
	Write_data(c+48);
	_delay_us(10);
	Write_data(':');
	Write_data(f+48);
	Write_data(e+48);
	_delay_us(10);
	
}