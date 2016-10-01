#include<avr/io.h>
#include<avr/interrupt.h>

#define  F_CPU 8000000UL
#include<util/delay.h>

#include "lcd4bit.h"

#define ALLSET(PORT) (PORT|=0xFF)
#define ALLCLR(PORT) (PORT&=0x00)
#define TOGGLE(PORT) (PORT^=0xFF)


char h = 0;
char m = 0;
char s = 0;
char tm[9];

void time_up();
void Timer0En();
char* time_1(char h,char m, char s);
void bit_toggal();

ISR (TIMER0_OVF_vect)
{
	static unsigned char count = 0;
	static char cou = 0;
	count++;
	cou++;
	if(cou>=20)
	{
		cou = 0;
	    bit_toggal();	
	}
	if(count>=40)
	{
		time_up();
		count = 0;
		
	}
}

void time_up()
{
	s++;
	if(s>=60){
		s=0;
		m++;
	}
	if(m>=60){
		m=0;
		h++;
	}
	if(h>=12){
		h=0;
	}
	char * tmp = time_1(h,m,s);
	gotoXy(4,0);
	Print_String(tmp);
}

char* time_1(char h,char m, char s)
{
    
	tm[8] = '\0';
    tm[2] = tm[5] = ':';
    if(h<10)
	{
	    tm[0] = '0';
		tm[1] = h+48;
	}else{
		tm[0] = (h/10)+48;
		tm[1] = (h%10)+48;
	}
	if(m<10)
	{
		tm[3] = '0';
		tm[4] = m+48;
	}else{
		tm[3] = (m/10)+48;
		tm[4] = (m%10)+48;
	}
	if(s<10)
	{
		tm[6] = '0';
		tm[7] = s+48;
	}else{
		tm[6] = (s/10)+48;
		tm[7] = (s%10)+48;
	}
	
    return tm;	
}

void bit_toggal()
{
	static char flag = 0;
	TOGGLE(PORTC);
    if(flag == 0){
		gotoXy(6,0);
		Write_data(' ');
		gotoXy(9,0);
		Write_data(' ');
		flag = 1;
	}else{
		/*gotoXy(7,1);
		Write_data(' ');
		gotoXy(10,1);
		Write_data(' ');*/
		flag = 0;
	}	
}

int main()
{
	Init_Ports();
	Init_LCD();
	ALLSET(DDRC);
	ALLSET(PORTC);
	
	Print_String("$ DigitalWorld $");
	gotoXy(0,1);
	Print_String(" * WelcomeYOU * ");
	
	_delay_ms(5000);
	
	Init_LCD();
	ALLCLR(PORTC);
	Print_String("    00:00:00");
	
	Timer0En();
	
	while(1);
	return 0;
}


void Timer0En()
{
	TCNT0 = 59;
	TCCR0 = 0x05;
	sei();
	TIMSK = (1<<TOIE0);
}


