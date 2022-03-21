/*
 * lcd.c
 *
 * Created: 15-03-2022 13:55:05
 *  Author: Apaul
 */ 


#include "lcd.h"

void lcd_busy(lcd_t *lcd) {
	
	gpio_config(lcd->bus[LCD_DB7],PIN_IN,PIN_LOW);
	gpio_set(lcd->bus[LCD_RS],PIN_LOW);	
	gpio_set(lcd->bus[LCD_RW],PIN_HIGH);
	gpio_set(lcd->bus[LCD_EN],PIN_HIGH);

	while(gpio_get(lcd->bus[LCD_DB7])) {
		
		gpio_set(lcd->bus[LCD_EN],PIN_LOW);
		gpio_set(lcd->bus[LCD_EN],PIN_HIGH);
	}
	
	gpio_config(lcd->bus[LCD_DB7],PIN_OUT,PIN_LOW);
	gpio_set(lcd->bus[LCD_RW],PIN_LOW);
}

void lcd_writeport(lcd_t *lcd,lcd_data_t d_chr) {
	
	
	
	
	if(lcd->mode == LCD_8BIT) {
		gpio_set(lcd->bus[LCD_DB0],d_chr.bits.b0);
		gpio_set(lcd->bus[LCD_DB1],d_chr.bits.b1);
		gpio_set(lcd->bus[LCD_DB2],d_chr.bits.b2);
		gpio_set(lcd->bus[LCD_DB3],d_chr.bits.b3);
	}
	
	gpio_set(lcd->bus[LCD_DB4],d_chr.bits.b4);
	gpio_set(lcd->bus[LCD_DB5],d_chr.bits.b5);
	gpio_set(lcd->bus[LCD_DB6],d_chr.bits.b6);
	gpio_set(lcd->bus[LCD_DB7],d_chr.bits.b7);
	
    gpio_set(lcd->bus[LCD_EN],PIN_HIGH);
	gpio_set(lcd->bus[LCD_EN],PIN_LOW);
}

void lcd_write(lcd_t *lcd,u8_t chr,lcd_data_type_t type )  {
	
	
	
	if(type == L_DATA)
		gpio_set(lcd->bus[LCD_RS],PIN_HIGH);
	 else
		gpio_set(lcd->bus[LCD_RS],PIN_LOW);
		
	gpio_set(lcd->bus[LCD_RW],PIN_LOW);
		
	if(lcd->mode == LCD_8BIT) 
		lcd_writeport(lcd,(lcd_data_t)chr);
		else {
			lcd_writeport(lcd,(lcd_data_t)(u8_t)((chr & 0xF0) >> 4));
			lcd_writeport(lcd, (lcd_data_t)(u8_t)(chr & 0x0F));
		}
		lcd_busy(lcd);
	
}
void lcd_writeCmd(lcd_t *lcd,u8_t chr) {
	lcd_write(lcd,chr,C_DATA);
}
void lcd_writeChar(lcd_t *lcd,u8_t chr) {
	lcd_write(lcd,chr,L_DATA);
}
void lcd_writeBuffer(lcd_t *lcd,const char *buffer,u16_t size) {
	u16_t counts = 0;
	while(counts < size) {
		lcd_writeChar(lcd,*( buffer + counts));
		counts++;
	}
}
void lcd_writeStr(lcd_t *lcd,const char *str) {
	u16_t size = strlen(str);
	lcd_writeBuffer(lcd,str,size);
}
void lcd_initialize(lcd_t *lcd, lcd_mode_t mode,...) {
	
	va_list ap;
	
	va_start(ap,mode);
	lcd->mode = mode;
	
	if(mode == LCD_4BIT) {
		
	    for (int i = 0 ; i  < 7; i ++)	{
			lcd->bus[i] = va_arg(ap,gpio_t *);
			if(lcd->bus[i] == 0)
			   continue;	
			gpio_config(lcd->bus[i],PIN_OUT,PIN_LOW);
	    }	
		
		lcd_writeCmd(lcd,0x02);
		lcd_writeCmd(lcd,0x28);
		lcd_writeCmd(lcd,0x0C);
		lcd_writeCmd(lcd,0x06);
		lcd_writeCmd(lcd,0x01);
		
	}else {
		
		for (int i = 0 ; i  < 11; i ++)	{
			lcd->bus[i] = va_arg(ap,gpio_t *);
			if(lcd->bus[i] == 0)
			   continue;
			gpio_config(lcd->bus[i],PIN_OUT,PIN_LOW);
		}	
			
		lcd_writeCmd(lcd,0x38);
		lcd_writeCmd(lcd,0x0C);
		lcd_writeCmd(lcd,0x06);
		lcd_writeCmd(lcd,0x01);
		lcd_writeCmd(lcd,0x80);
	}
	
	va_end(ap);
}