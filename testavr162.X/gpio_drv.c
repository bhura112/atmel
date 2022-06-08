/*
 * gpio_drv.c
 *
 * Created: 01-06-2022 12:30:50
 *  Author: HP
 */ 

#include "gpio_drv.h"

volatile uint8_t *gpiomap[][3] ={
	{ &DDRA,&PORTA,&PINA},
	{ &DDRB,&PORTB,&PINB},
	{ &DDRC,&PORTC,&PINC},
	{ &DDRD,&PORTD,&PIND},
	{ &DDRE,&PORTE,&PINE},	
};



uint8_t GPIO_RegBitWrite(gpio_obj_t *gpio,bool bitv,uint8_t reg)
{
	 uint8_t regv = *gpiomap[gpio->port][reg];
	 regv &= ~(1 << gpio->pin);
	 regv |= (bitv << gpio->pin);
	  *gpiomap[gpio->port][reg] = regv;
	 return regv;
}

bool GPIO_RegBitRead(gpio_obj_t *gpio,uint8_t reg)
{
	uint8_t regv = *gpiomap[gpio->port][reg];
	
	return (bool)( regv & (1 << gpio->pin) ? 1:0);
}


void GPIO_PinConfig(gpio_obj_t *gpio,bool dir,bool state)
{
	GPIO_RegBitWrite(gpio,dir,GPIO_REG_DDR);
	GPIO_RegBitWrite(gpio,state,GPIO_REG_POR);
}

void GPIO_PinSet(gpio_obj_t *gpio, bool state)
{
    GPIO_RegBitWrite(gpio,state,GPIO_REG_POR);	
}

bool GPIO_PinGet(gpio_obj_t *gpio)
{
	return GPIO_RegBitRead(gpio,GPIO_REG_PIN);
}