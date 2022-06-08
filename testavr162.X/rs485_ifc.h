/*
 * rs485_ifc.h
 *
 * Created: 01-06-2022 12:08:08
 *  Author: HP
 */ 


#ifndef RS485_IFC_H_
#define RS485_IFC_H_


#include "common_utils.h"

void RS485_Initialize(long USART_BAUDRATE);
unsigned char RS485_ReadChar( void );
void RS485_WriteChar(char ch);
void RS485_WriteBuffer(const char *str, uint16_t len);
void RS485_WriteString(const char *str);



#endif /* RS485_IFC_H_ */