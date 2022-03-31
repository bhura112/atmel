/*
* lcd.c
*
* Created: 22-03-2022 09:42:43
*  Author: Apaul
*/

#include "lcd.h"
#include <stdio.h>

#define lcd_delay(d) for(int i = 0; i < d; i++)

void lcd_busy(lcd_t *lcd) {
	
	gpio_config(&lcd->data_bus[7],PIN_IN,PIN_LOW);
	
	gpio_set(&lcd->rs,PIN_LOW);
	lcd_delay(100);
	gpio_set(&lcd->rw,PIN_HIGH);
	
	uint8_t checkflag = 0;
	
	do {
		gpio_set(&lcd->en,PIN_LOW);
		lcd_delay(100);
		gpio_set(&lcd->en,PIN_HIGH);
		
		checkflag = gpio_get(&lcd->data_bus[7]);
		
		if(lcd->mode == LCD_4BIT) {
			gpio_set(&lcd->en,PIN_LOW);
			lcd_delay(100);
			gpio_set(&lcd->en,PIN_HIGH);
		}
	}while(checkflag);
	gpio_set(&lcd->rw,PIN_LOW);
	lcd_delay(100);
	
	gpio_set(&lcd->en,PIN_HIGH);	
	lcd_delay(100);
	
	gpio_config(&lcd->data_bus[7],PIN_OUT,PIN_LOW);
	lcd_delay(100);
	
}

void lcd_portWrite(lcd_t *lcd, lcd_data_t data) {	
	gpio_set(&lcd->en,PIN_HIGH);
	if(lcd->mode == LCD_8BIT) {		
		gpio_set(&lcd->data_bus[0] ,data.b0);
		gpio_set(&lcd->data_bus[1] ,data.b1);
		gpio_set(&lcd->data_bus[2] ,data.b2);
		gpio_set(&lcd->data_bus[3] ,data.b3);
	}
	gpio_set(&lcd->data_bus[4] ,data.b4);
	gpio_set(&lcd->data_bus[5] ,data.b5);
	gpio_set(&lcd->data_bus[6] ,data.b6);
	gpio_set(&lcd->data_bus[7] ,data.b7);
	
	
	gpio_set(&lcd->en,PIN_LOW);
}
void lcd_write(lcd_t *lcd,u8_t chr,u8_t type) {
	
	gpio_set(&lcd->rs,type);
	
	gpio_set(&lcd->rw,PIN_LOW);
	
	if(lcd->mode == LCD_4BIT) {
		
		lcd_portWrite(lcd,(lcd_data_t)(uint8_t)(chr & 0xF0));
		lcd_portWrite(lcd,(lcd_data_t)(uint8_t)((chr  & 0x0F) << 4));
	}else
		lcd_portWrite(lcd,(lcd_data_t)((uint8_t)chr));
}

void lcd_writeCmd(lcd_t *lcd,u8_t chr) {
	lcd_write(lcd,chr,LCD_CMD_TYPE);
	lcd_busy(lcd);
}

void lcd_writeData(lcd_t *lcd,u8_t chr) {
	
	if(chr == 0)
		chr = ' ';
		
	lcd_write(lcd,chr,LCD_DATA_TYPE);
}

void lcd_writeBuffer(lcd_t *lcd,u8_t *buffer,u16_t size) {
	
}

void lcd_writeStr(lcd_t *lcd,u8_t *str) {
	
}

void lcd_disp_clear(lcd_t *lcd){
	memset(lcd->lines.buffer,0,LCD_MAX_COL * LCD_MAX_ROW);
}
void lcd_disp_update(lcd_t *lcd) {
	
    uint8_t offset[4] = {0x80,0xC0,0x90,0xD0};
	
	if (memcmp(lcd->lines.buffer, lcd->p_lines.buffer,sizeof(lcd->p_lines.buffer)))
	{
		for (int i = 0; i < 2; i++)
		{
			lcd_writeCmd(lcd,offset[i]);
			
			for(int j = 0 ; j < 16; j++) {
				lcd_writeData(lcd,lcd->lines.line[i].data[j]);
			}
		}

		lcd->p_lines = lcd->lines;
	}
}

void lcd_printf(lcd_t *lcd,u8_t x, u8_t y,const char *fmt,...) {

	va_list ap;
	
	va_start(ap,fmt);

	vsprintf(&lcd->lines.line[y].data[x],fmt,ap);
	
	va_end(ap);
	
	lcd_disp_update(lcd);
		
}

void lcd_task(lcd_t *lcd) {
	lcd_disp_update(lcd);
}

void lcd_initialize(lcd_t *lcd,u8_t mode,...) {

	lcd->mode = mode;
	
	va_list ap;
	va_start(ap,mode);
	
	lcd->rs = va_arg(ap,gpio_t);
	lcd->rw = va_arg(ap,gpio_t);
	lcd->en = va_arg(ap,gpio_t);
	
	gpio_config(&lcd->rs,PIN_OUT,PIN_LOW);
	gpio_config(&lcd->rw,PIN_OUT,PIN_LOW);
	gpio_config(&lcd->en,PIN_OUT,PIN_LOW);
	
	if(lcd->mode==LCD_8BIT){
		for(int i = 0; i < 4 ;i++) {
			lcd->data_bus[i] = va_arg(ap,gpio_t);
			gpio_config(&lcd->data_bus[i],PIN_OUT,PIN_LOW);
		}
	}
	
	for(int i = 4; i < 8 ;i++) {
		lcd->data_bus[i] = va_arg(ap,gpio_t);
		gpio_config(&lcd->data_bus[i],PIN_OUT,PIN_LOW);
	}
	
	va_end(ap);
	
	if(lcd->mode == LCD_4BIT) {
		lcd_writeCmd(lcd,0x02);
		lcd_writeCmd(lcd,0x28);
	}else
	lcd_writeCmd(lcd,0x38);
	
	lcd_writeCmd(lcd,0x0C);
	lcd_writeCmd(lcd,0x06);
	lcd_writeCmd(lcd,0x01);
	lcd_writeCmd(lcd,0x80);
}