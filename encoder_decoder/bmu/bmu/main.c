/*
 * main.c
 *
 * Created: 3/15/2022 12:06:20 PM
 *  Author: Apaul
 */ 

#define F_CPU 1000000UL
#include <util/delay.h>
#include <stdlib.h>

#include "gpio.h"
#include "lcd.h"
#include <stdio.h>
#define LCD_PIN(p,n) ({gpio_t *mpin = (gpio_t *)malloc(sizeof(gpio_t));\
						       mpin->port = p;\
					           mpin->pin = n; mpin;})
	
gpio_t transmit_pin = {PORT_D,PIN_0};
	gpio_t btn_pin = {PORT_C,PIN_0};
lcd_t lcd = {0};
	
	void Start_Transmission( gpio_t *io);
    void Write_Transmisstion ( gpio_t *io ,u8_t chr);	
	void Stop_Transmission( gpio_t *io);
	
int main(void)
{
	
	gpio_config(&transmit_pin,PIN_OUT,PIN_HIGH); 
	gpio_config(&btn_pin,PIN_OUT,PIN_LOW); 
	
	lcd_initialize(&lcd,LCD_8BIT,
								LCD_PIN(PORT_A , PIN_0),
								LCD_PIN(PORT_A , PIN_1),
								LCD_PIN(PORT_A , PIN_2),
								
								LCD_PIN(PORT_B , PIN_0),
								LCD_PIN(PORT_B , PIN_1),
								LCD_PIN(PORT_B , PIN_2),
								LCD_PIN(PORT_B , PIN_3),
								LCD_PIN(PORT_B , PIN_4),
								LCD_PIN(PORT_B , PIN_5),
								LCD_PIN(PORT_B , PIN_6),
								LCD_PIN(PORT_B , PIN_7)
								);
    u8_t x = 'A';
	while(1)
    {
		Write_Transmisstion(&transmit_pin,x);
        lcd_writeChar(&lcd,x);
		_delay_ms(700);
		lcd_writeCmd(&lcd,0x01);
		x++;
    }
}

	void Idle_Transmission(gpio_t *io) {
       gpio_set(io,1);
	   _delay_ms(1);
	}
	void Start_Transmission( gpio_t *io) {
		gpio_set(io,0);
		_delay_ms(1);
	}
	
	void Stop_Transmission( gpio_t *io) {


		gpio_set(io,1);
		_delay_ms(1);
	}
	
	void Write_Transmisstion ( gpio_t *io ,u8_t chr) {
		
		u8_t i = 0;
		
		Start_Transmission(io);
		
		for(i = 0 ; i < 8; i++) { 
			
			gpio_set(io,((chr & (1 << i))?1:0));
			_delay_ms(1);
			
				
		}
		gpio_set(io,0);	
			_delay_ms(1);
		Stop_Transmission(io);
		Idle_Transmission(io);
	}
	
