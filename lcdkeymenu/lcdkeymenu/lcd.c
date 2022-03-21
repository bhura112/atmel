#include <util/delay.h>

#include "lcd.h"

uint8_t row_offset[4] = {0x80, 0xC0, 0x90, 0xD0};
uint8_t bit4ModeCmd[] = {0x02, 0x28, 0x0C, 0x06, 0x01};

void Lcd_Update(lcd_t *lcd) {

    Gpio_PinWrite(&lcd->db4, lcd->data.bits.b0);
    Gpio_PinWrite(&lcd->db5, lcd->data.bits.b1);
    Gpio_PinWrite(&lcd->db6, lcd->data.bits.b2);
    Gpio_PinWrite(&lcd->db7, lcd->data.bits.b3);

    Gpio_PinWrite(&lcd->en, GPIO_HIGH);
    Gpio_PinWrite(&lcd->en, GPIO_LOW);
}

void Lcd_Busy(lcd_t *lcd) {

    Gpio_PinConfig(&lcd->db7, GPIO_IN, GPIO_LOW);
    Gpio_PinWrite(&lcd->rw, GPIO_HIGH);

    while (Gpio_PinRead(&lcd->db7)) {
        Gpio_PinWrite(&lcd->en, GPIO_HIGH);
        _delay_us(1);
        Gpio_PinWrite(&lcd->en, GPIO_LOW);
    }
    Gpio_PinConfig(&lcd->db7, GPIO_OUT, GPIO_LOW);
}

void Lcd_WriteChar(lcd_t *lcd, uint8_t chr) {

    Gpio_PinWrite(&lcd->rs, GPIO_HIGH);

    Gpio_PinWrite(&lcd->rw, GPIO_LOW);

    lcd->data.byte = ((chr >> 4) & 0x0F);

    Lcd_Update(lcd);

    lcd->data.byte = (chr & 0x0F);

    Lcd_Update(lcd);
    _delay_us(1);
    Lcd_Busy(lcd);

}

void Lcd_WriteCmdd(lcd_t *lcd, uint8_t cmd) {

    Gpio_PinWrite(&lcd->rs, GPIO_LOW);

    Gpio_PinWrite(&lcd->rw, GPIO_LOW);

    lcd->data.byte = ((cmd >> 4) & 0x0F);
    Lcd_Update(lcd);

    lcd->data.byte = (cmd & 0x0F);
    Lcd_Update(lcd);

}

void Lcd_SetCursorBlink(lcd_t *lcd, uint8_t blink) {

    if (blink)
        return Lcd_WriteCmdd(lcd, 0x0F);
    else
        return Lcd_WriteCmdd(lcd, 0x0C);
}

void Lcd_SetCursor(lcd_t *lcd, uint8_t pos) {

    lcd->cur_pos = pos;
}

void Lcd_Clear(lcd_t *lcd) {

    memset(lcd->lines.buffer, 0, sizeof (lcd->lines.buffer));
}

void Lcd_Printf(lcd_t *lcd, uint8_t x, uint8_t y, const char *fmt, ...) {

    va_list ap;

    va_start(ap, fmt);

    vsprintf((char *) &lcd->lines.data.line[y][x], fmt, ap);

    va_end(ap);
}

void Lcd_Initialize(lcd_t *lcd) {

    Gpio_PinConfig(&lcd->rs, GPIO_OUT, GPIO_LOW);
    Gpio_PinConfig(&lcd->rw, GPIO_OUT, GPIO_LOW);
    Gpio_PinConfig(&lcd->en, GPIO_OUT, GPIO_LOW);

    Gpio_PinConfig(&lcd->db4, GPIO_OUT, GPIO_LOW);
    Gpio_PinConfig(&lcd->db5, GPIO_OUT, GPIO_LOW);
    Gpio_PinConfig(&lcd->db6, GPIO_OUT, GPIO_LOW);
    Gpio_PinConfig(&lcd->db7, GPIO_OUT, GPIO_LOW);

        int i = 0;

    for (i = 0; i < 5; i++) {

    Lcd_WriteCmdd(lcd, bit4ModeCmd[i]);

    }

    memset(lcd->lines.buffer, 0, sizeof ( lcd->lines.buffer));

    lcd->prev_lines = lcd->lines;

    _delay_ms(200);
}

void Lcd_Task(lcd_t *lcd) {

    if (memcmp(lcd->prev_lines.buffer, lcd->lines.buffer, sizeof (lcd->prev_lines.buffer)) || lcd->cur_pos != lcd->prev_cur_pos) {

        uint8_t rows = 0, cols = 0;

        for (rows = 0; rows < LCD_MAX_ROWS; rows++) {

            Lcd_WriteCmdd(lcd, row_offset[rows]);

            for (cols = 0; cols < LCD_MAX_COLS; cols++) {

                Lcd_WriteChar(lcd, lcd->lines.data.line[rows][cols]);
            }

            Lcd_WriteCmdd(lcd, row_offset[rows] + lcd->cur_pos);
        }



        lcd->prev_cur_pos = lcd->cur_pos;

        lcd->prev_lines = lcd->lines;

     }
}