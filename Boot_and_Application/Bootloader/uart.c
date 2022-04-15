/*
 * uart.c
 *
 * Created: 08-04-2022 16:53:36
 *  Author: HP
 */ 

#include "uart.h"

int i = 0;
#define FSOC 1000000

uartRxCallback uartRx = 0;

ISR(USART_RXC_vect) {
	
	if(uartRx)
		uartRx(UDR);
}

void Uart_TxChar(uint8_t chr) {
	
    while ( !UCSRAbits.udre );
   UDR = chr;
  
   
}

void Uart_Initialize(uint32_t baudrate) {

	uint16_t UBRR = 0;
	
	sei();
	
	UCSRAbits.u2x = 1;
    
	UCSRBbits.rxcie = 1;
	
	UCSRBbits.rxen = 1;
	UCSRBbits.txen = 1;
	
	UCSRCbits.ursel = 1;
	UCSRCbits.ucsz0 = 1;
	UCSRCbits.ucsz1 = 1;
	
	UBRR = (FSOC/(  ( !UCSRAbits.u2x * 8 + 8 ) * baudrate)) - 1;
	UBRRH = (uint8_t)(UBRR >> 8);
	UBRRL = (uint8_t)(UBRR);
}