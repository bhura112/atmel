/*
 * keypad.c
 *
 * Created: 31-03-2022 15:01:47
 *  Author: Apaul
 */ 

#include "keypad.h"
#include <util/delay.h>

#include "lcd.h"

extern lcd_t lcd;

void keypad_initialize(keypad_t *keypad) {
	
	for (int i = 0; i < KEYPAD_MAX_KEY; i++)
	{
		keypad->map[i].state = 0;
		
		gpio_config(&keypad->map[i].row,PIN_IN,PIN_LOW);
		gpio_config(&keypad->map[i].col,PIN_OUT,PIN_HIGH);
	}
}

void keypad_key_scan(key_t *key) {
	
	switch(key->state) {
		
		case 0:
		
		if (key->alph_time_completed)
		{
			key->fresh = 0;
			key->finilisized = 1;
			key->pressed     = 1;
		}
		
		if(!key->alph_timer) 
		{
			key->fresh = 0;
			key->finilisized = 0;
			key->pressed     = 0;
		}
		gpio_set(&key->col,PIN_LOW);
		_delay_ms(1);
		PORTC = 0x01;
		if (!gpio_get(&key->row))
		{
			key->state++;
		}
		gpio_set(&key->col,PIN_HIGH);
		_delay_ms(1);
		break;
		
		case 1:
		PORTC = 0x02;
		_delay_ms(1);
		gpio_set(&key->col,PIN_LOW);
		if (gpio_get(&key->row))
		{
			
		}else
			key->state = 3;
		gpio_set(&key->col,PIN_HIGH);
		break;
		
		case 2:
		break;
		
		case 3:
		
		gpio_set(&key->col,PIN_LOW);
		
		if (gpio_get(&key->row))
		{
			key->finilisized = 1;
			key->pressed = 1;
			key->state = 0;
		}
		
		gpio_set(&key->col,PIN_HIGH);
		
		if(key->finilisized) {
			lcd_writeData(&lcd,key->val);
			_delay_ms(10);
		}
		break;
		
		default:
		break;
	}
}

void keypad_update(keypad_t *keypad) {
	
	for (int i = 0 ; i  < KEYPAD_MAX_KEY; i ++)
	{
		if(keypad->map[i].finilisized && keypad->map[i].pressed) {
			//PORTE = keypad->curr_key = keypad->map[i].val;
		}
	}
}

void keypad_scan(keypad_t *keypad) {
	
	keypad_key_scan(&keypad->map[keypad->key_counts]);
	
	keypad->key_counts++;
	
	if(keypad->key_counts > KEYPAD_MAX_KEY)
	keypad->key_counts = 0;
}

void keypad_task(keypad_t *keypad) {
	keypad_update(keypad);
	keypad_scan(keypad);
}