/*
 * led.cpp
 *
 * Created: 12-05-2022 14:59:53
 * Author : HP
 */ 

#include <avr/io.h>
#define F_CPU 1000000UL
#include <util/delay.h>

#include "gpio.h"

int main(void)
{
	
	//DDRB = 0x01;
	//
	//
	//while (1)
	//{
		//PORTB = 0x01;
		//_delay_ms(1000);
		//PORTB = 0x00;
		//_delay_ms(1000);
	//}

	bio.d.pin0 = 1;

    while (1) 
    {
		bio.p.pin0 = 1;
		_delay_ms(1000);
		bio.p.pin0 = 0;
		_delay_ms(1000);
		
    }
}

