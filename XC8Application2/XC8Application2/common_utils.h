/*
 * common_utils.h
 *
 * Created: 01-06-2022 12:03:46
 *  Author: HP
 */ 


#ifndef COMMON_UTILS_H_
#define COMMON_UTILS_H_

#define F_CPU 14745600UL
#include <xc.h>
#include <string.h>
#include <util/delay.h>
#include <stdbool.h>


//#define USART_BAUDRATE 9600
#define BAUD_PRESCALE(x) (((F_CPU / (x * 16UL))) - 1)




#endif /* COMMON_UTILS_H_ */