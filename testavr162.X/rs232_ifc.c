/*
 * rs232_ifc.c
 *
 * Created: 01-06-2022 11:58:59
 *  Author: HP
 */
#include "rs232_ifc.h"
#include "sab82532.h"

FILE RS232STREAM_wr = FDEV_SETUP_STREAM(RS232_StreamWriteChar, 0, _FDEV_SETUP_WRITE);

#define CLI_BUFFER_SIZE 64

uint8_t cli_buffer[CLI_BUFFER_SIZE] = {0};

uint8_t cli_chrCounts = 0;

bool cli_cmd_completed = false;

const char *ok_err_str[] = {
    "ERROR",
    "OK"
};
const char *nwline = "\r\n";

ISR(USART0_RXC_vect) {

    cli_buffer[cli_chrCounts] = UDR0;

    //putchar(cli_buffer[cli_chrCounts]);

    if (cli_buffer[cli_chrCounts] == '\r') {

        cli_buffer[cli_chrCounts] = 0;
        cli_cmd_completed = true;
    } else
        cli_chrCounts++;
}

uint8_t hex2Byte(uint8_t ch) {
    if (ch >= '0' && ch <= '9')
        return (uint8_t) (ch - '0');
    if (ch >= 'A' && ch <= 'F')
        return (uint8_t) (ch - 'A' + 10);
    if (ch >= 'a' && ch <= 'f')
        return (uint8_t) (ch - 'a' + 10);

    return 0xFF;
}

const char *reg_name[] = {
    "STAR",
    "MODE",
    "TIMR",
    "DAFO",
    "RFC ",
    "CCR0",
    "CCR1",
    "CCR2",
    "CCR3",
    "VSTR",
    "IPC ",
    "CCR4"
};

void CLI_Interface(void) {
    uint16_t reg_addr = 0;
    uint16_t reg_len = 0;
    uint16_t reg_val = 0;
    unsigned char *reg_addr_ptr = 0;
    if (cli_cmd_completed) {

        switch (cli_buffer[0]) {
            case 'd':
                printf(nwline);
                printf("SAB %s : 0x%02x \r\n", reg_name[0], SABReg(SAB_STAR).byte);
                printf("SAB %s : 0x%02x \r\n", reg_name[1], SABReg(SAB_MODE).byte);
                printf("SAB %s : 0x%02x \r\n", reg_name[2], SABReg(SAB_TIMR).byte);
                printf("SAB %s : 0x%02x \r\n", reg_name[3], SABReg(SAB_DAFO).byte);
                printf("SAB %s : 0x%02x \r\n", reg_name[4], SABReg(SAB_RFC).byte);
                printf("SAB %s : 0x%02x \r\n", reg_name[5], SABReg(SAB_CCR0).byte);
                printf("SAB %s : 0x%02x \r\n", reg_name[6], SABReg(SAB_CCR1).byte);
                printf("SAB %s : 0x%02x \r\n", reg_name[7], SABReg(SAB_CCR2).byte);
                printf("SAB %s : 0x%02x \r\n", reg_name[8], SABReg(SAB_CCR3).byte);
                printf("SAB %s : 0x%02x \r\n", reg_name[9], SABReg(SAB_VSTR).byte);
                printf("SAB %s : 0x%02x \r\n", reg_name[10], SABReg(SAB_IPC).byte);
                printf("SAB %s : 0x%02x \r\n", reg_name[11], SABReg(SAB_CCR4).byte);
                break;
            case 'p':
                PORTB |= (1 << PB1);
                _delay_ms(50);
                printf(ok_err_str[!SAB82532_xMemPutFChar(&sabObj, 'A')]);
                _delay_ms(50);
                 PORTB &= ~(1 << PB1);
                break;
            case 't':
                 PORTB |= (1 << PB1);
                _delay_ms(50);
                printf(ok_err_str[!SAB82532_xMemPutTChar(&sabObj, 'A')]);
                 _delay_ms(50);
                 PORTB &= ~(1 << PB1);
                break;
            case 'x':
                PORTB |= (1 << PB1);
                _delay_ms(50);
                
                memcpy(sabObj.yfifo,"Hello",5);
                sabObj.yfifo_size = 5;
                
                printf(ok_err_str[!SAB82532_TransmitFifo(&sabObj)]);
                 _delay_ms(50);
                 PORTB &= ~(1 << PB1);
                break;
                
            case 'y':
                PORTB |= (1 << PB1);
                _delay_ms(50);
                
                memcpy(sabObj.yfifo,"WORLD",5);
                sabObj.yfifo_size = 5;
                
                printf(ok_err_str[!SAB82532_TransmitFifo(&sabObj)]);
                 _delay_ms(50);
                 PORTB &= ~(1 << PB1);
                 
                break;
            case 'f':
                printf(ok_err_str[!SAB82532_xMemFlushFifo(&sabObj)]);
                break;

            case 'r':
            {

                reg_addr_ptr = &cli_buffer[3];

                while (*reg_addr_ptr) {
                    if (*reg_addr_ptr == ' ') {
                        *reg_addr_ptr = 0;

                        break;
                    } else
                        reg_addr = (reg_addr << 4) + hex2Byte(*(reg_addr_ptr));
                    reg_addr_ptr++;
                }

                reg_addr_ptr++;

                if (*reg_addr_ptr == 0)
                    reg_len = 1;
                else {
                    while (*reg_addr_ptr) {
                        reg_len = (reg_len << 4) + hex2Byte(*(reg_addr_ptr));
                        reg_addr_ptr++;
                    }
                }
                printf(nwline);
                for (int i = 0; i < reg_len; i++)
                    printf("%04x:0x%02x \n\r", (reg_addr + i), SABReg(reg_addr + i).byte);
            }
                break;
            case 'w':
            {

                reg_addr_ptr = &cli_buffer[3];

                while (*reg_addr_ptr) {
                    if (*reg_addr_ptr == ' ') {
                        *reg_addr_ptr = 0;

                        break;
                    } else
                        reg_addr = (reg_addr << 4) + hex2Byte(*(reg_addr_ptr));
                    reg_addr_ptr++;
                }

                reg_addr_ptr++;

                while (*reg_addr_ptr) {
                    reg_val = (reg_val << 4) + hex2Byte(*(reg_addr_ptr));
                    reg_addr_ptr++;
                }

                SABReg(reg_addr).byte = reg_val;

                printf("%04x : 0x%02x\n\r", reg_addr, SABReg(reg_addr).byte);
            }

                break;
            default:
                if (cli_buffer[0] == '\r' || cli_buffer[0] == '\0') {

                } else
                    printf("=:unknwon\n\r");
                break;
        }

        printf("\r\nsab >");

        memset((void *) cli_buffer, 0, CLI_BUFFER_SIZE);
        cli_chrCounts = 0;
        cli_cmd_completed = false;
    }
}

void RS232_Initialize(long USART_BAUDRATE) {

    UCSR0B |= (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0); /* Turn on the transmission and reception */
    UCSR0C |= (1 << URSEL0) | (1 << UCSZ00) | (1 << UCSZ01); /* Use 8-bit character sizes */

    UBRR0L = BAUD_PRESCALE(USART_BAUDRATE); /* Load lower 8-bits of the baud rate value */
    UBRR0H = (BAUD_PRESCALE(USART_BAUDRATE) >> 8); /*Load upper 8-bits*/

    stdout = &RS232STREAM_wr;
}

unsigned char RS232_ReadChar(void) {
    while ((UCSR0A & (1 << RXC0)) == 0); /*Do nothing until data have been received*/
    return (UDR0); /* return the byte*/
}

int RS232_StreamWriteChar(char c, FILE * stream) {

    while (!(UCSR0A & (1 << UDRE0))); /*Wait for empty transmit buffer*/
    UDR0 = c;
    while (!(UCSR0A & (1 << TXC0))); /*Wait for empty transmit buffer*/

    return 0;
}

void RS232_WriteChar(char ch) {
    while (!(UCSR0A & (1 << UDRE0))); /*Wait for empty transmit buffer*/
    UDR0 = ch;
    while (!(UCSR0A & (1 << TXC0))); /*Wait for empty transmit buffer*/
}

void RS232_WriteBuffer(const char *str, uint16_t len) {
    for (int i = 0; i < len; i++) {
        RS232_WriteChar(str[i]);
    }
}

void RS232_WriteString(const char *str) {
    uint16_t len = strlen(str);
    RS232_WriteBuffer(str, len);
}

