/* 
 * File:   uart.h
 * Author: Bhura Malik
 *
 * Created on March 4, 2022, 3:38 PM
 */

#ifndef UART_H
#define	UART_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>

    unsigned char Uart_GetKey();
    void Uart_Initialize(unsigned int baud);
    void Uart_WriteChar(uint8_t chr);
    void Uart_WriteBuffer(const char *buffer, uint16_t length);
    void Uart_WriteStr(const char *buffer);

#ifdef	__cplusplus
}
#endif

#endif	/* UART_H */

