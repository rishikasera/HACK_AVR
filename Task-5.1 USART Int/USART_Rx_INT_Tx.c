#include   <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/interrupt.h>

#define BAUD 9600
#define BAUDRATE ((F_CPU)/(BAUD*16UL)-1)        // set baudrate value for UBRR
#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

void uart_init (void);
void uart_transmit (unsigned char data);
unsigned char uart_recieve (void);
void SerialInterruptDisable();
void SerialInterruptEnable();

void LedInit()
{
	DDRC = 0xFF;
	PORTC = 0xFF;
}
void LedOn()
{
	PORTC = 0x00;
}
void LedOff()
{
	PORTC = 0xFF;
}
int main()
{
	LedInit();
	uart_init();
	SerialInterruptEnable();
	LedOn();
	_delay_ms(1000);
	uart_transmit('h');
	LedOff();
	_delay_ms(1000);
	uart_transmit('e');
	LedOn();
	_delay_ms(1000);
	uart_transmit('l');
	LedOff();
	_delay_ms(1000);
	uart_transmit('l');
	LedOn();
	_delay_ms(1000);
	uart_transmit('o');
	LedOff();
	_delay_ms(1000);
	uart_transmit(' ');
	LedOn();
	_delay_ms(1000);
	uart_transmit('w');
	LedOff();
	_delay_ms(1000);
	uart_transmit('o');
	LedOn();
	_delay_ms(1000);
	uart_transmit('r');
	LedOff();
	_delay_ms(1000);
	uart_transmit('l');
	LedOn();
	_delay_ms(1000);
	uart_transmit('d');

	while(1){
		//char ch = uart_recieve();
		//uart_transmit(ch);
	}
}

ISR(USART_RXC_vect)
{
	char ReceivedByte;
	ReceivedByte = UDR;
	uart_transmit(ReceivedByte);
}


void uart_init (void)
{
	UBRRH=(BAUDRATE>>8);
	UBRRL=BAUDRATE;                                                 //set baud rate
	UCSRB|=(1<<TXEN)|(1<<RXEN);                     //enable receiver and transmitter
	UCSRC|=(1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);// 8bit data format
}


void uart_transmit (unsigned char data)
{
	while (!( UCSRA & (1<<UDRE)));                  // wait while register is free
	UDR = data;                                                     // load data in the register
}


unsigned char uart_recieve (void)
{
	while(!((UCSRA) & (1<<RXC)));                     // wait while data is being received
	return UDR;                                                     // return 8-bit data
}


void SerialInterruptDisable()
{
	UCSRB = (0<<RXEN)|(0<<TXEN);
}


void SerialInterruptEnable()
{
	UBRRH = (BAUD_PRESCALE >> 8);
	UBRRL = BAUD_PRESCALE;
	UCSRC |= (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);
	UCSRB |= (1 << RXEN) | (1 << TXEN);
	UCSRB |= (1 << RXCIE);
	sei();
}
