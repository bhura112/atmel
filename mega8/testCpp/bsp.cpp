/*
 * bsp.cpp
 *
 * Created: 06-05-2022 17:46:21
 *  Author: HP
 */ 
#include "bsp.h"


unsigned char GpioPortSfrAddress[GPIO_MAX_PORTS][GPIO_MAX_PORT_REGS] ={
	{ 0x17, 0x18, 0x16 }, //portB
	{ 0x14, 0x15, 0x13 }, //portC
	{ 0x11, 0x12, 0x10 } //portD
};

void * operator new(size_t size) {
	
	return malloc(size);
}

void operator delete(void *ptr) {
	
	return free(ptr);
}