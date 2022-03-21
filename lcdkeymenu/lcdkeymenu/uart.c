#include "uart.h"
#define FOSC 1000000UL
#define MYUBRR(BAUD_RATE) (unsigned int)(FOSC/16/BAUD_RATE-1)

unsigned char uartRxCharBuffer[64], uart_key;
unsigned short uartRxCharBufferSize;

 ISR(USART0_RX_vect) {

    uartRxCharBuffer[uartRxCharBufferSize] = UDR0;
    if (uartRxCharBuffer[uartRxCharBufferSize] == '\r')

        uart_key = uartRxCharBuffer[uartRxCharBufferSize - 1];

        if (uartRxCharBufferSize++ > 63)
        uartRxCharBufferSize = 0;
}

unsigned char Uart_GetKey() {

    unsigned char key = uart_key;
    uart_key = 0;
    return key;
}
void Uart_Initialize(unsigned int baud) {

    unsigned int ubrr = MYUBRR(baud);

    UCSR0B = (1 << TXEN0) | (1 << RXEN0) | (1 << RXCIE0);

    UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);

    UBRR0L = (unsigned char) ubrr;

    UBRR0H = (unsigned char) ubrr >> 8;
}

void Uart_WriteChar(uint8_t chr) {

    while (!(UCSR0A & (1 << UDRE)));
    UDR0 = chr;
}

void Uart_WriteBuffer(const char *buffer, uint16_t length) {

    uint16_t count = 0;

    while (count < length) {
        Uart_WriteChar(*(buffer + count));
        count++;
    }
}

void Uart_WriteStr(const char *buffer) {
    uint16_t len = strlen(buffer);
    Uart_WriteBuffer(buffer, len);
}
