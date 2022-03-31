/*
 * lcd.h
 *
 * Created: 22-03-2022 09:42:56
 *  Author: Apaul
 */ 


#ifndef LCD_H_
#define LCD_H_

#include "gpio.h"

#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include <util/delay.h>
#define LCD_4BIT 0
#define LCD_8BIT 1

#define LCD_CMD_TYPE  0
#define LCD_DATA_TYPE 1

typedef struct {
	u8_t *data;
}lcd_lines_t;

typedef union {
	u8_t byte;
	struct {
		u8_t b0:1;
		u8_t b1:1;
		u8_t b2:1;
		u8_t b3:1;
		u8_t b4:1;
		u8_t b5:1;
		u8_t b6:1;
		u8_t b7:1;
		};
	}lcd_data_t;
typedef struct {
  gpio_t rs;
  gpio_t rw;
  gpio_t en;
  gpio_t data_bus[8];
  	
  lcd_lines_t line;
  lcd_lines_t p_line;
  
 struct {
	   u8_t mode:1;
	   u8_t :7;
	 };
}lcd_t;

void lcd_busy(lcd_t *lcd);

void lcd_write(lcd_t *lcd,u8_t chr,u8_t type);

void lcd_writeCmd(lcd_t *lcd,u8_t chr);

void lcd_writeData(lcd_t *lcd,u8_t chr);

void lcd_writeBuffer(lcd_t *lcd,u8_t *buffer,u16_t size);

void lcd_writeStr(lcd_t *lcd,u8_t *str);

void lcd_printf(lcd_t *lcd,u8_t x, u8_t y,...);

void lcd_task(lcd_t *lcd);

void lcd_initialize(lcd_t *lcd,u8_t mode,...);


#endif /* LCD_H_ */