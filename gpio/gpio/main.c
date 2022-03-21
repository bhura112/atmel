/*
 * gpio.c
 *
 * Created: 21-03-2022 11:33:28
 * Author : Apaul
 */ 

#include <avr/io.h>

#define F_CPU 1000000UL

#include <util/delay.h>
#include "gpio.h"

gpio_t led = {PORT_A,PIN_0};
int main(void)
{
    gpio_config(&led,PIN_OUT,PIN_LOW);
	
    while (1) 
    {
		gpio_set(&led,PIN_HIGH);
		_delay_ms(1000);
		
		gpio_set(&led,PIN_LOW);
		_delay_ms(1000);
		
    }
}

