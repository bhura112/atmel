/*
 * uart.c
 *
 * Created: 08-04-2022 16:53:36
 *  Author: HP
 */ 

#include "uart.h"
#define FSOC 1000000
int i = 0;
uint8_t Uart_RxChar() {
	
	if (UCSRAbits.rxc)
	{
		return UDR;
	}else
		return  -1;
}
void Uart_TxChar(uint8_t chr) {
	
    while ( !UCSRAbits.udre );
   UDR = chr;
  
   
}
void Uart_TxBuffer(const char *buf,uint16_t size) {
	
	for (uint16_t i = 0; i < size; i++)
	{
		Uart_TxChar(*(buf + i));
	}
}

void Uart_Initialize(uint32_t baudrate) {

	uint16_t UBRR = 0;
	
	UCSRAbits.u2x = 1;

	UCSRBbits.rxen = 1;
	UCSRBbits.txen = 1;
	
	UCSRCbits.ursel = 1;
	UCSRCbits.ucsz0 = 1;
	UCSRCbits.ucsz1 = 1;
	
	UBRR = (FSOC/(  ( !UCSRAbits.u2x * 8 + 8 ) * baudrate)) - 1;
	UBRRH = (uint8_t)(UBRR >> 8);
	UBRRL = (uint8_t)(UBRR);
}

void Uart_Task() {
	
	uint8_t cmdval = Uart_RxChar();
	
	switch(cmdval ) {
		case '0':
		Uart_TxBuffer("boot mode :",11);
		_delay_ms(1000);
		break;
		case '1':
		Uart_TxBuffer("app mode :",10);
		_delay_ms(1000);
		break;
		default:
		break;
	}
}