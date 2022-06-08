/*
 * rs485_ifc.c
 *
 * Created: 01-06-2022 12:08:25
 *  Author: HP
 */ 

#include "rs485_ifc.h"


void RS485_Initialize(long USART_BAUDRATE)
{
	UCSR1B |= (1 << RXEN1) | (1 << TXEN1);   /* Turn on the transmission and reception */
	UCSR1C |= (1 << URSEL1) | (1 << UCSZ10) | (1 << UCSZ11); /* Use 8-bit character sizes */

	UBRR1L = BAUD_PRESCALE(USART_BAUDRATE); 					/* Load lower 8-bits of the baud rate value */
	UBRR1H = (BAUD_PRESCALE(USART_BAUDRATE) >> 8);			/*Load upper 8-bits*/
}

unsigned char RS485_ReadChar( void )
{
	while ((UCSR1A & (1 << RXC1)) == 0); /*Do nothing until data have been received*/
	return(UDR1);				/* return the byte*/
}

void RS485_WriteChar(char ch)
{
	while (! (UCSR1A & (1<<UDRE1))); /*Wait for empty transmit buffer*/
	UDR1 = ch ;
	while (! (UCSR1A & (1<<TXC1))); /*Wait for empty transmit buffer*/
}

void RS485_WriteBuffer(const char *str, uint16_t len)
{
	for (int i = 0; i < len;i ++)
	{
		RS485_WriteChar(str[i]);
	}
}
void RS485_WriteString(const char *str)
{
	uint16_t len = strlen(str);
	RS485_WriteBuffer(str,len);
}
