/*
 * gpio_btn_led.c
 *
 * Created: 21-03-2022 11:46:07
 * Author : Apaul
 */ 

#include <avr/io.h>
#include "gpio.h"


gpio_t led = {PORT_B,PIN_0};
	
gpio_t button = {PORT_A,PIN_5};
	
int main(void)
{

	gpio_config(&led,PIN_OUT,PIN_LOW);
	gpio_config(&button,PIN_IN,PIN_LOW);
	
    while (1) 
    {
		if(gpio_get(&button))
		gpio_set(&led,PIN_HIGH);
		else
		gpio_set(&led,PIN_LOW);
    }
}

