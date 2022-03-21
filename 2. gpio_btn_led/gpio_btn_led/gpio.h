/*
 * IncFile1.h
 *
 * Created: 15-03-2022 12:08:46
 *  Author: Apaul
 */ 


#ifndef GPIO_H_
#define GPIO_H_
#ifdef __XC8__
#include <xc.h>
#else
#include <avr/io.h>
#endif
#define MAX_PORT_REG 3

typedef unsigned char u8_t ;
typedef unsigned short u16_t;

typedef enum {
	PIN_LOW,
	PIN_HIGH
}gpio_state_t;
	
typedef enum {
	PIN_IN,
	PIN_OUT,
}gpio_dir_t;

typedef enum {
#ifdef PORTA
	PORT_A,
#endif
#ifdef PORTB
	PORT_B,
#endif
#ifdef PORTC
	PORT_C,
#endif
#ifdef PORTD
	PORT_D,
#endif
#ifdef PORTE
	PORT_E,
#endif
#ifdef PORTF
PORT_F,
#endif
#ifdef PORTG
PORT_G,
#endif
	MAX_PORT_AVL
}gpio_ports_t;

typedef enum {
	PIN_0,
	PIN_1,
	PIN_2,
	PIN_3,
	PIN_4,
	PIN_5,
	PIN_6,
	PIN_7,
}gpio_pins_t;

typedef struct {
	gpio_ports_t port;
	gpio_pins_t pin;
	}gpio_t;
	
	void gpio_setdir(gpio_t *io,gpio_dir_t dir);
	void gpio_set(gpio_t *io,gpio_state_t state);	
	gpio_state_t gpio_get(gpio_t *io);
	
	void gpio_config(gpio_t *io,gpio_dir_t dir,gpio_state_t state);
	void gpio_toggle(gpio_t *io);
	

#endif /* INCFILE1_H_ */