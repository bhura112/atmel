/*
 * lcd.c
 *
 * Created: 22-03-2022 09:34:14
 * Author : Apaul
 */ 

#include <avr/io.h>

#include "lcd.h"

lcd_t lcd;

int main(void)
{
    lcd_initialize(&lcd,LCD_8BIT,(gpio_t){PORT_A,PIN_0},
								 (gpio_t){PORT_A,PIN_1},
								 (gpio_t){PORT_A,PIN_2},
											
								(gpio_t){PORT_B,PIN_0},
								(gpio_t){PORT_B,PIN_1},
								(gpio_t){PORT_B,PIN_2},
								(gpio_t){PORT_B,PIN_3},
								(gpio_t){PORT_B,PIN_4},
								(gpio_t){PORT_B,PIN_5},
								(gpio_t){PORT_B,PIN_6},
								(gpio_t){PORT_B,PIN_7});   							
									
    while (1) 
    {
		lcd_writeData(&lcd,'A');
        _delay_ms(1000);
    }
}

