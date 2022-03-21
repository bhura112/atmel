/*
 * lcd.h
 *
 * Created: 15-03-2022 13:55:58
 *  Author: Apaul
 */ 


#ifndef LCD_H_
#define LCD_H_

#include "gpio.h"
#include <string.h>
#include <stdarg.h>

typedef enum {
LCD_RS,
LCD_RW,
LCD_EN,
LCD_DB0,
LCD_DB1,
LCD_DB2,
LCD_DB3,
LCD_DB4,
LCD_DB5,
LCD_DB6,
LCD_DB7	
}lcd_bus_t;

typedef union {
	
	struct {
		u8_t b0:1;
		u8_t b1:1;
		u8_t b2:1;
		u8_t b3:1;
		u8_t b4:1;
		u8_t b5:1;
		u8_t b6:1;
		u8_t b7:1;
		}bits;
		u8_t byte;
}lcd_data_t;

typedef enum {
	LCD_4BIT,
	LCD_8BIT
}lcd_mode_t;

typedef enum {
	L_DATA,
	C_DATA
	}lcd_data_type_t;
	
typedef struct {
	gpio_t *bus[11];
	u8_t mode;
}lcd_t;

void lcd_busy(lcd_t *lcd);

void lcd_write(lcd_t *lcd,u8_t chr,lcd_data_type_t type );
void lcd_writeCmd(lcd_t *lcd,u8_t chr);
void lcd_writeChar(lcd_t *lcd,u8_t chr);
void lcd_writeBuffer(lcd_t *lcd,const char *buffer,u16_t size);
void lcd_writeStr(lcd_t *lcd,const char *str);
void lcd_initialize(lcd_t *lcd,lcd_mode_t mode,...);

#endif /* LCD_H_ */