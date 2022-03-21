/* 
 * File:   lcd.h
 * Author: Bhura Malik
 *
 * Created on March 3, 2022, 5:39 PM
 */

#ifndef LCD_H
#define	LCD_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
    
#include "gpio.h"

#define LCD_MAX_ROWS 4
#define LCD_MAX_COLS 16
    
    typedef union {

        struct lcd_lines_struct_t {
            uint8_t line[LCD_MAX_ROWS][LCD_MAX_COLS];

        } data;

        uint8_t buffer[sizeof (struct lcd_lines_struct_t)];

    } lcd_lines_t;

    typedef struct {

        gpio_t rs;
        gpio_t rw;
        gpio_t en;

        gpio_t db4;
        gpio_t db5;
        gpio_t db6;
        gpio_t db7;

        lcd_lines_t lines;
        lcd_lines_t prev_lines;
        union {

            uint8_t byte;

            struct {
                uint8_t n_m : 4;
                uint8_t n_l : 4;
            } n;

            struct {
                uint8_t b0 : 1;
                uint8_t b1 : 1;
                uint8_t b2 : 1;
                uint8_t b3 : 1;
                uint8_t b4 : 1;
                uint8_t b5 : 1;
                uint8_t b6 : 1;
                uint8_t b7 : 1;
            } bits;
        } data;

        struct {
            uint8_t cur_pos : 4;
            uint8_t prev_cur_pos : 4;
        };
    } lcd_t;

    void Lcd_Clear(lcd_t *lcd);

    void Lcd_Printf(lcd_t *lcd, uint8_t x, uint8_t y, const char *fmt, ...);

    void Lcd_SetCursor(lcd_t *lcd, uint8_t pos);

    void Lcd_SetCursorBlink(lcd_t *lcd, uint8_t blink);

    void Lcd_Initialize(lcd_t *lcd);

    void Lcd_Task(lcd_t *lcd);
    
#ifdef	__cplusplus
}
#endif

#endif	/* LCD_H */

