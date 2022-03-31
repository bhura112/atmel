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
	lcd_initialize(&lcd,LCD_4BIT,
		(gpio_t){PORT_A,PIN_0},
		(gpio_t){PORT_A,PIN_1},
		(gpio_t){PORT_A,PIN_2},
		
		(gpio_t){PORT_B,PIN_4},
		(gpio_t){PORT_B,PIN_5},
		(gpio_t){PORT_B,PIN_6},
		(gpio_t){PORT_B,PIN_7});
	
	int i = 0;
	
	while (1)
	{
		lcd_disp_clear(&lcd);
		
		lcd_printf(&lcd,0,0,"LCD 16X2");
		lcd_printf(&lcd,0,1,"COUNTS : %d",i++);
		
		_delay_ms(1000);
	}
}

