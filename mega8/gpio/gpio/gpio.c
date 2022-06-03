/*
 * gpio.c
 *
 * Created: 29-04-2022 15:14:40
 *  Author: HP
 */ 
#include "gpio.h"

volatile unsigned char *gpio_ports_map[GPIO_MAX_PORTS][GPIO_MAX_REGISTERS]= {
	
	{&DDRB,&PORTB,&PINB},
	
	{&DDRC,&PORTC,&PINC},
		
	{&DDRD,&PORTD,&PIND},
};

static gpio_pin_state_t GPIO_ReadWriteReg(gpio_pin_obj_t *gpio,gpio_ports_reg_t reg,uint8_t val) {
	
	if (gpio->port >= GPIO_MAX_PORTS)
	{
		gpio->state = 0;
		gpio->status = GPIO_ERROR;
		return 0; 
	}
	
	if(reg == GPIO_OUTPUT_REG || reg == GPIO_DIRECTION_REG) {
	
		uint8_t regval = *gpio_ports_map[gpio->port][reg];
		
		regval &= ~(1 << gpio->pin);
		
		regval |= (val << gpio->pin);
		
		*gpio_ports_map[gpio->port][reg] = regval;
	}
	
	if(reg == GPIO_OUTPUT_REG || reg == GPIO_INPUT_REG) {
	     gpio->state =  *gpio_ports_map[gpio->port][reg] & (1 << gpio->pin);
		 
		 return  gpio->state;
	}
	
	return 0;
}

void GPIO_PinConfig(gpio_pin_obj_t *gpio,gpio_pin_dir_t dir,gpio_pin_state_t state) {
	
	GPIO_ReadWriteReg(gpio,GPIO_DIRECTION_REG,dir);
	
	GPIO_ReadWriteReg(gpio,GPIO_OUTPUT_REG,state);
	
}

gpio_pin_state_t GPIO_PinRead(gpio_pin_obj_t *gpio) {
	
	gpio_pin_state_t state = GPIO_LOW;
	
	state = GPIO_ReadWriteReg(gpio,GPIO_INPUT_REG,0);
	
	return state;
}

void GPIO_PinWrite(gpio_pin_obj_t *gpio,gpio_pin_state_t state) {
	
	GPIO_ReadWriteReg(gpio,GPIO_OUTPUT_REG,state);
}

void GPIO_PinToggle(gpio_pin_obj_t *gpio) {
	
	GPIO_PinWrite(gpio,!GPIO_PinRead(gpio));
	
}