/*
 * gpio.h
 *
 * Created: 12-05-2022 15:01:50
 *  Author: HP
 */ 


#ifndef GPIO_H_
#define GPIO_H_

#include <avr/io.h>

typedef union {
	struct  
	{
		uint8_t pin0:1;
		uint8_t pin1:1;
		uint8_t pin2:1;
		uint8_t pin3:1;
		uint8_t pin4:1;
		uint8_t pin5:1;
		uint8_t pin6:1;
		uint8_t pin7:1;
	};
	struct {
		uint8_t lsb4:4;
		uint8_t msb4:4;
		};
		uint8_t pins;
}port_reg_t;

typedef struct  
{
	port_reg_t r;
	port_reg_t d;
	port_reg_t p;
}port_t;

#define bio    (*(volatile port_t *) (0x16 + __SFR_OFFSET))

#endif /* GPIO_H_ */