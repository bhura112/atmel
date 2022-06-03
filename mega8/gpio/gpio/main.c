/*
 * gpio.c
 *
 * Created: 29-04-2022 15:11:25
 * Author : HP
 */ 

#include <avr/io.h>
#include "gpio.h"

gpio_pin_obj_t redled = {PORT_B,PORT_PIN_7,{0,0}};
	
int main(void)
{
		
	GPIO_PinConfig(&redled,GPIO_OUTPUT,GPIO_LOW);    
	
    while (1) 
    {
		GPIO_PinToggle(&redled);
    }
}

