/*
 * bsp.h
 *
 * Created: 06-05-2022 17:46:33
 *  Author: HP
 */ 


#ifndef BSP_H_
#define BSP_H_

#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <stdlib.h>
#include <stdint.h>

#include <stddef.h>

#define HIGH 1
#define LOW  0

#define INPUT  0	
#define OUTPUT 1

	
typedef enum {
	GPIO_DIRECTION_REG,
	GPIO_OUTPUT_REG,
	GPIO_INPUT_REG,
	GPIO_MAX_PORT_REGS
}GpioSfrRegs_t;

typedef enum  {
	GPIO_PORT_B,
	GPIO_PORT_C,
	GPIO_PORT_D,
	GPIO_MAX_PORTS,
}GpioSfrPorts_t ;


extern unsigned char GpioPortSfrAddress[GPIO_MAX_PORTS][GPIO_MAX_PORT_REGS];

#endif /* BSP_H_ */