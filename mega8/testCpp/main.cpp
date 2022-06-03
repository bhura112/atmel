/*
 * testCpp.cpp
 *
 * Created: 06-05-2022 10:58:29
 * Author : HP
 */ 

#define F_CPU 1000000UL
#include <util/delay.h>

#include "LedClass.h"
#include "ButtonClass.h"
#include "LcdClass.h"

int main(void)
{
    
	LedClass *redLed = new LedClass(GPIO_PORT_B,0);
	ButtonClass *switch1 = new ButtonClass(GPIO_PORT_B,1);
	LcdClass lcd;
	
    while (1) 
    {
		redLed->setState(switch1->read());
    }
}

