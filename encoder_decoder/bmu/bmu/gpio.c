/*
* CFile1.c
*
* Created: 15-03-2022 12:08:18
*  Author: Apaul
*/

#include "gpio.h"

volatile u8_t *gpiomap[MAX_PORT_AVL][MAX_PORT_REG] = {
#ifdef PORTA
	{&DDRA,&PORTA,&PINA},
#endif

#ifdef PORTB
	{&DDRB,&PORTB,&PINB},
#endif

#ifdef PORTC	
		
	{&DDRC,&PORTC,&PINC},
#endif

#ifdef PORTD		
		
	{&DDRD,&PORTD,&PIND},
#endif

#ifdef PORTE
	{&DDRE,&PORTE,&PINE},
#endif

#ifdef PORTF
{&DDRF,&PORTF,&PINF},
#endif

#ifdef PORTG
{&DDRG,&PORTG,&PING},
#endif

};

void gpio_setdir(gpio_t *io,gpio_dir_t dir) {
	u8_t d_reg = *gpiomap[io->port][0];
	d_reg &= ~(1 << io->pin);
	d_reg |= (dir << io->pin);
	*gpiomap[io->port][0] = d_reg;
}

void gpio_set(gpio_t *io,gpio_state_t state) {
	
	u8_t s_reg = *gpiomap[io->port][1];
	s_reg &= ~(1 << io->pin);
	s_reg |= (state << io->pin);
	*gpiomap[io->port][1] = s_reg;
}

gpio_state_t gpio_get(gpio_t *io) {
	
	u8_t r_reg = *gpiomap[io->port][2];
	if(r_reg & (1 << io->pin))
		return PIN_HIGH;
	else
		return PIN_LOW;
}

void gpio_config(gpio_t *io,gpio_dir_t dir,gpio_state_t state) {
	gpio_setdir(io,dir);
	gpio_set(io,state);
}

void gpio_toggle(gpio_t *io) {
	gpio_set(io,!gpio_get(io));
}