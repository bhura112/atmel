/*
 * rs232_ifc.h
 *
 * Created: 01-06-2022 11:59:16
 *  Author: HP
 */ 


#ifndef RS232_IFC_H_
#define RS232_IFC_H_

#include "common_utils.h"

extern const char *ok_err_str[];
extern const char *nwline;

void RS232_Initialize(long USART_BAUDRATE);
unsigned char RS232_ReadChar( void );
int RS232_StreamWriteChar(char c, FILE * stream);
void  RS232_WriteChar(char ch);
void RS232_WriteBuffer(const char *str, uint16_t len);
void RS232_WriteString(const char *str);
void CLI_Interface( void );

#endif /* RS232_IFC_H_ */