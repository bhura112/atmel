/*
 * seg.h
 *
 * Created: 21-03-2022 12:05:07
 *  Author: Apaul
 */ 


#ifndef SEG_H_
#define SEG_H_

#include "gpio.h"
#define F_CPU 1000000UL
#include <util/delay.h>
#include <stdarg.h>
#include <avr/pgmspace.h>
#include <stdio.h>

#define SEG_PIN(p,n) ((gpio_t){p,n})
	
	#define SEG_CATHODE 1
	#define SEG_ANODE 0
	
typedef enum {
	SEG_BUS_A,
	SEG_BUS_B,
	SEG_BUS_C,
	SEG_BUS_D,
	SEG_BUS_E,
	SEG_BUS_F,
	SEG_BUS_G,
	SEG_BUS_H,
	}seg_data_bus_t;
	
typedef struct  
{
	gpio_t data_bus[8];
	gpio_t cntrl_bus[8];
	
	char max_digits;
	u8_t segOn,segOff,digOff,digOn;
}segment_t;

void segment_config(segment_t *seg,u8_t cntrl_bus,...);

void segment_write(segment_t *seg,u8_t dig, u8_t val);

void segment_writeChar(segment_t *seg,u8_t dig,u8_t chr) ;

void segment_writeInt(segment_t *seg,int val);
#endif /* SEG_H_ */