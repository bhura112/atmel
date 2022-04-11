/*
 * Application.c
 *
 * Created: 15/10/2019 09:24:54
 * Author : uid23021
 */ 

#include <avr/io.h>
#define F_CPU 1000000UL
#include <util/delay.h>

int main(void)
{
    DDRD = 0xFF;
	
    while (1) 
    {
		PORTD = 0x00;
		_delay_ms(1000);
		PORTD = 0xFF;
		_delay_ms(1000);
    }
}

