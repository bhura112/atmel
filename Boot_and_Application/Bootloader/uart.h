/*
 * uart.h
 *
 * Created: 08-04-2022 16:53:53
 *  Author: HP
 */ 


#ifndef UART_H_
#define UART_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 1000000UL
#include <util/delay.h>

typedef void (*uartRxCallback)(uint8_t);
typedef void (*uartTxCallback)(uint8_t);
typedef volatile union {
    uint8_t u8;
	struct  
	{
		uint8_t mpcm:1;
		uint8_t u2x:1;
		uint8_t upe:1;
		uint8_t dor:1;
		uint8_t fe:1;
		uint8_t udre:1;
		uint8_t txc:1;
		uint8_t rxc:1;
	};
}ucsra_bits_t;

typedef volatile union {
    uint8_t u8;
	struct  
	{
		uint8_t txb8:1;
		uint8_t rxb8:1;
		uint8_t ucsz2:1;
		uint8_t txen:1;
		uint8_t rxen:1;
		uint8_t udrie:1;
		uint8_t txcie:1;
		uint8_t rxcie:1;
	};
}ucsrb_bits_t;

typedef volatile union {
    uint8_t u8;
	struct  
	{
		uint8_t ucpol:1;
		uint8_t ucsz0:1;
		uint8_t ucsz1:1;
		uint8_t usbs:1;
		uint8_t upm0:1;
		uint8_t upm1:1;
		uint8_t umsel:1;
		uint8_t ursel:1;
	};
}ucsrc_bits_t;

#define UCSRAbits (*((ucsra_bits_t *)(&UCSRA)))
#define UCSRBbits (*((ucsrb_bits_t *)(&UCSRB)))
#define UCSRCbits (*((ucsrc_bits_t *)(&UCSRC)))

extern uartRxCallback uartRx;

void Uart_Initialize(uint32_t baudrate);

void Uart_TxChar(uint8_t chr);

#endif /* UART_H_ */