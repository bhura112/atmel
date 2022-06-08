/*
 * rs232_ifc.c
 *
 * Created: 01-06-2022 11:58:59
 *  Author: HP
 */ 
#include "rs232_ifc.h"

FILE RS232STREAM = FDEV_SETUP_STREAM(RS232_StreamWriteChar, NULL, _FDEV_SETUP_WRITE);

void RS232_Initialize(long USART_BAUDRATE)
{
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);   /* Turn on the transmission and reception */
	UCSR0C |= (1 << URSEL0) | (1 << UCSZ00) | (1 << UCSZ01); /* Use 8-bit character sizes */

	UBRR0L = BAUD_PRESCALE(USART_BAUDRATE); 					/* Load lower 8-bits of the baud rate value */
	UBRR0H = (BAUD_PRESCALE(USART_BAUDRATE) >> 8);			/*Load upper 8-bits*/
	
	stdout = &RS232STREAM;
}

unsigned char RS232_ReadChar( void )
{
	while ((UCSR0A & (1 << RXC0)) == 0); /*Do nothing until data have been received*/
	return(UDR0);				/* return the byte*/
}

int RS232_StreamWriteChar(char c, FILE * stream) {
	
	while (! (UCSR0A & (1<<UDRE0))); /*Wait for empty transmit buffer*/
	UDR0 = c ;
	while (! (UCSR0A & (1<<TXC0))); /*Wait for empty transmit buffer*/
	
	return 0;
}

void  RS232_WriteChar(char ch)
{
	while (! (UCSR0A & (1<<UDRE0))); /*Wait for empty transmit buffer*/
	UDR0 = ch ;
	while (! (UCSR0A & (1<<TXC0))); /*Wait for empty transmit buffer*/
}

void RS232_WriteBuffer(const char *str, uint16_t len)
{
	for (int i = 0; i < len;i ++)
	{
		RS232_WriteChar(str[i]);
	}
}

void RS232_WriteString(const char *str)
{
	uint16_t len = strlen(str);
	RS232_WriteBuffer(str,len);
}

