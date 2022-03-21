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
	
gpio_t receiver_pin = {PORT_D,PIN_0};
lcd_t lcd = {0};
	
int main(void)
{
	gpio_config(&receiver_pin,PIN_IN,PIN_HIGH); //idle
	
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
	u8_t counts = 0,val;
    u8_t state = 0;
	while(1)
    {		
		switch(state) {
			case 0:
				if(!gpio_get(&receiver_pin)) {
					counts = 0;
					state++; 
					  _delay_us(1020);
				}
			break;
			
			case 1:
			   val |= gpio_get(&receiver_pin) << counts;
			   
			   _delay_us(1020);
			   
			   if(counts > 6)
			    state++;
				counts++;
				break;
			case 2:
			     if(gpio_get(&receiver_pin)) {
					 lcd_writeChar(&lcd,val);
					  _delay_ms(700);
					  lcd_writeCmd(&lcd,0x01);
			           state = 0;
					   val = 0;
				 }
			break;
		}
	}
}