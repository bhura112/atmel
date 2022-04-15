/*
 * boot.h
 *
 * Created: 12-04-2022 10:43:36
 *  Author: HP
 */ 


#ifndef BOOT_H_
#define BOOT_H_
#include <inttypes.h>
#include <avr/boot.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#include "uart.h"

typedef struct {
	uint8_t start;
	uint8_t len;
	uint8_t cmd;
	uint8_t data_end[65];
}boot_buffer_struct_t;

typedef union {
	boot_buffer_struct_t data;
	uint8_t bytes[sizeof(boot_buffer_struct_t)];
}boot_buffer_t;


typedef struct {
	boot_buffer_t buffer;
	uint8_t size;
	struct
	{
		uint8_t start_rec:1;
		uint8_t rx_completed:1;
		uint8_t valid_frame:1;
		uint8_t pending_frame:1;
		uint8_t :5;
	};
}boot_frame_t;

#define BootInterfaceRxCallbackSet(c)   uartRx = c
#define BootInterfaceTx(c)              Uart_TxChar(c)
#define BootInterfaceInitialize(b)      Uart_Initialize(b)


void BootInitialize(void);
void BootRxHandler(uint8_t);
void BootTxHandler(uint8_t);
void BootProccessFrame(boot_frame_t *);



#endif /* BOOT_H_ */