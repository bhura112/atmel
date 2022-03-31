/*
 * keypad.h
 *
 * Created: 31-03-2022 15:02:02
 *  Author: Apaul
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "gpio.h"

#define KEYPAD_MAX_KEY 16

typedef struct {
	gpio_t row;
	gpio_t col;
	uint8_t val;
	
	uint16_t alph_timer;
	
	struct {
	  
	  uint16_t state:4;
	  
	  uint16_t  fresh:1;
	  uint16_t  finilisized:1;
	  uint16_t  pressed:1;
	  uint16_t  long_press:1;
	  uint16_t  alph_time_completed:1;
	 
	};
}key_t;

typedef struct {
    	
		key_t map[KEYPAD_MAX_KEY];
		
		uint8_t key_counts;
		
		uint8_t curr_key;
		
		
}keypad_t;


void keypad_initialize(keypad_t *keypad);
void keypad_key_scan(key_t *key);
void keypad_task(keypad_t *keypad);

#endif /* KEYPAD_H_ */