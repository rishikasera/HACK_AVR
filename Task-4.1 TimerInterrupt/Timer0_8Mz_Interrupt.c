#include<avr/io.h>
#include<avr/interrupt.h>
#define  F_CPU 16000000UL
#define ALLSET(PORT) (PORT|=0xFF)
#define ALLCLR(PORT) (PORT&=0x00)
#define TOGGLE(PORT) (PORT^=0xFF)

ISR (TIMER0_OVF_vect)
{
	static unsigned char count = 0;
	count++;
	if(count>=40)
	{
		count = 0;
		TOGGLE(PORTC);
	}
}

void Timer0En();
int main()
{
	ALLSET(DDRC);
	ALLSET(DDRC);
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


/*
   TIMER 0
   NORMAL MODE 
   XTAL        8 MHz
   PreeScaller 1024
  



#include<avr/io.h>
#define F_CPU 8000000UL
#define ALLSET(PORT) (PORT|=0xFF)
#define ALLCLR(PORT) (PORT&=0x00)

void Timer0Delay(unsigned char);
int main(void)
{
	ALLSET(DDRC);
	ALLSET(PORTC);
    while(1)
	{
		ALLCLR(PORTC); 
		Timer0Delay(40);
        ALLSET(PORTC);
		Timer0Delay(40);		
	}
}

void Timer0Delay(unsigned char count)
{
	while(count-->0)
	{
		TCNT0 = 59;                              //  8Mz / 1024 = 8KHz  =  .125m Sec                  =  7.8125 KHz   =  .128m Sec 
		TCCR0 = 0x05;                           //  255 - 5 = 200    200 * .125 = 25mSec             =  196 * .128   = 25.088  Actual
		while((TIFR&(1<<TOV0))==0);             //  25m * 40  = 1Sec. Aprox                          =  255 - 196 = 59  
		TCCR0 = 0;
		TIFR |= (1<<TOV0); 
	}
	
}
*/