/* 
 * File:   gpio.h
 * Author: Bhura Malik
 *
 * Created on March 3, 2022, 5:46 PM
 */

#ifndef GPIO_H
#define	GPIO_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <avr/io.h>

    typedef enum {
        PORT_A,
        PORT_B,
        PORT_C,
        PORT_D,
        PORT_E
    } ports_t;

    typedef enum {
        PIN_0,
        PIN_1,
        PIN_2,
        PIN_3,
        PIN_4,
        PIN_5,
        PIN_6,
        PIN_7
    } pins_t;

    typedef enum {
        GPIO_LOW,
        GPIO_HIGH
      
    } gpio_state_t;

    typedef enum {
        GPIO_IN,
        GPIO_OUT
    } gpio_dir_t;


    typedef struct gpio_struct_t {
        uint8_t _port;
        uint8_t _pin;
    } gpio_t;

    void Gpio_PinConfig(gpio_t *io, gpio_dir_t dir, gpio_state_t state);
    void Gpio_PinWrite(gpio_t *io, gpio_state_t state);
    void Gpio_PinToggle(gpio_t *io);
    uint8_t Gpio_PinRead(gpio_t *io);
    
#ifdef	__cplusplus
}
#endif

#endif	/* GPIO_H */

