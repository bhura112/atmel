/*
 * gpio_drv.h
 *
 * Created: 01-06-2022 12:31:09
 *  Author: HP
 */ 


#ifndef GPIO_DRV_H_
#define GPIO_DRV_H_

#include "common_utils.h"

#define GPIO_LVL_HIGH 1
#define GPIO_LVL_LOW  0

#define GPIO_DIR_OUT  1
#define GPIO_DIR_IN   0

#define GPIO_REG_DDR 0
#define GPIO_REG_POR 1
#define GPIO_REG_PIN 2

#define GPIO_DIR_OUT_bm  0x01
#define GPIO_DIR_IN_bm   0x02
#define GPIO_DIR_HIGH_bm 0x04
#define GPIO_DIR_LOW_bm  0x08

typedef enum {
	GPIO_PORT_A,
	GPIO_PORT_B,
	GPIO_PORT_C,
	GPIO_PORT_D,
	GPIO_PORT_E,
	}gpio_ports_t;
	
typedef enum {
	GPIO_PIN_0,
	GPIO_PIN_1,
	GPIO_PIN_2,
	GPIO_PIN_3,
	GPIO_PIN_4,
	GPIO_PIN_5,
	GPIO_PIN_6,
	GPIO_PIN_7,
	}gpio_pins_t;
	
typedef struct  
{
	uint8_t port;
	uint8_t pin;
	bool state;
}gpio_obj_t;



void GPIO_PinConfig(gpio_obj_t *gpio,bool dir,bool state);
void GPIO_PinSet(gpio_obj_t *gpio, bool state);
bool GPIO_PinGet(gpio_obj_t *gpio);

#endif /* GPIO_DRV_H_ */