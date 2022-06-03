/*
 * gpio.h
 *
 * Created: 29-04-2022 15:14:51
 *  Author: HP
 */ 


#ifndef GPIO_H_
#define GPIO_H_


#include <avr/io.h>
#define GPIO_OK 0
#define GPIO_ERROR 1
typedef enum {
	GPIO_DIRECTION_REG,
	GPIO_OUTPUT_REG,
	GPIO_INPUT_REG,
	GPIO_MAX_REGISTERS
}gpio_ports_reg_t;

typedef enum {
	
	#ifdef PORTA
		POART_A,
	#endif
	
	#ifdef  PORTB
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
	#ifdef PORTH
		PORT_H,
	#endif
	GPIO_MAX_PORTS	
}gpio_ports_t;

typedef enum {
	PORT_PIN_0,
	PORT_PIN_1,
	PORT_PIN_2,
	PORT_PIN_3,
	PORT_PIN_4,
	PORT_PIN_5,
	PORT_PIN_6,
	PORT_PIN_7	
}gpio_pins_t;

typedef enum {
	GPIO_LOW,
	GPIO_HIGH
}gpio_pin_state_t;

typedef enum {
	
	GPIO_INPUT,
	GPIO_OUTPUT
}gpio_pin_dir_t;

typedef struct
{
	uint8_t port;
	uint8_t pin;
	struct
	{
		uint8_t state:1;
		uint8_t status:1;
		uint8_t :6;
	};

}gpio_pin_obj_t;

void GPIO_PinConfig(gpio_pin_obj_t *,gpio_pin_dir_t ,gpio_pin_state_t );

gpio_pin_state_t GPIO_PinRead(gpio_pin_obj_t *);

void GPIO_PinWrite(gpio_pin_obj_t *,gpio_pin_state_t);

void GPIO_PinToggle(gpio_pin_obj_t *);


#endif /* GPIO_H_ */