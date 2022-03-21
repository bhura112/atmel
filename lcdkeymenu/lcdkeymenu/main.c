

#define F_CPU 1000000UL
#include <util/delay.h>

#include "timer.h"
#include "lcd.h"
#include "menu.h"
#include "uart.h"

lcd_t lcdObj = {

    .rs =
    {PORT_A, PIN_0},
    .rw =
    {PORT_A, PIN_1},
    .en =
    {PORT_A, PIN_2},

    .db4 =
    {PORT_A, PIN_4},
    .db5 =
    {PORT_A, PIN_5},
    .db6 =
    {PORT_A, PIN_6},
    .db7 =
    {PORT_A, PIN_7},
};

menu_t muObj;

gpio_t buttonBack = {PORT_D, PIN_4};
gpio_t buttonDown = {PORT_D, PIN_5};
gpio_t buttonUp = {PORT_D, PIN_6};
gpio_t buttonEnter = {PORT_D, PIN_7};
gpio_t led1 = {PORT_C, PIN_0};

uint16_t led_blink_speed = 1000; //ms



timer_t getKeyTimer = {0};
timer_t led1_timer = {0};

unsigned char getKey() {

    static uint8_t state = 0;

    uint8_t key = 0;

    if (((Gpio_PinRead(&buttonEnter) ? 'E' : 0))) {
        key = 'E';
    }

    if (((Gpio_PinRead(&buttonUp) ? 'U' : 0))) {
        key = 'U';
    }

    if (((Gpio_PinRead(&buttonDown) ? 'D' : 0))) {
        key = 'D';
    }

    if (((Gpio_PinRead(&buttonBack) ? 'C' : 0))) {
        key = 'C';
    }
    switch (state) {
        case 0:
            if (key) {
                state++;
                Timer_Start(&getKeyTimer, 100, TIMER_STOP_AFTER_COMPLETED);

            }
            break;
        case 1:
            if (Timer_IsCompleted(&getKeyTimer)) {
                if (key)
                    state++;
                else
                    state = 0;
            }
            break;
        case 2:

            state = 0;
            return key;
    }
    return 0;
}

void Lcd_MenuScreen(lcd_t *lcd, const char *buffer) {

    char *token, *rest;
    uint8_t line_count = 0;
    char localBuffer[256] = {0};

    Lcd_Clear(lcd);
    memcpy(localBuffer, buffer, strlen(buffer));
    token = strtok_r(localBuffer, "\n", &rest);

    do {
        Lcd_Printf(lcd, 0, line_count++, token);
        token = strtok_r(0, "\n", &rest);
    } while (token);

}

void Lcd_DefaultScreen(lcd_t *lcd) {

    Lcd_Clear(lcd);
    Lcd_Printf(lcd, 0, 0, "LCD 16X2");
    Lcd_Printf(lcd, 0, 1, "PRESS ENTER");
}

unsigned char test_buttons(void *ptr) {

    sprintf((char *) muObj.out, "TEST BUTTON\nFUNCTION EXEC\n");

    if (muObj.key == 'C') {
        return 1;
    }
    return 0;
}

unsigned char test_lcd(void *ptr) {

    sprintf((char *) muObj.out, "TEST LCD\nFUNCTION EXEC\n");

    if (muObj.key == 'C') {
        return 1;
    }
    return 0;
}

unsigned char test_led(void *ptr) {

    sprintf((char *) muObj.out, "TEST LED\nFUNCTION EXEC\n");

    if (muObj.key == 'C') {
        return 1;
    }
    return 0;
}
menu_window_opt_t menu_testOptions[] = {
    { .opt_heading_ptr = "TEST BUTTONS",
        .type = MENU_TYP_FUN,
        .ptr = &test_buttons,
        .params = &muObj,
        .next_menu = 0,
        .ret_val = RETURN_TO_MAIN_MENU,},

    { .opt_heading_ptr = "TEST LCD",
        .type = MENU_TYP_FUN,
        .ptr = &test_lcd,
        .params = &muObj,
        .next_menu = 0,
        .ret_val = RETURN_TO_MAIN_MENU,},

    { .opt_heading_ptr = "TEST LED",
        .type = MENU_TYP_FUN,
        .ptr = &test_led,
        .params = &muObj,
        .next_menu = 0,
        .ret_val = RETURN_TO_MAIN_MENU,},


};

#define TEST_WINDOW_LEN sizeof(menu_testOptions)/sizeof(menu_window_opt_t)
menu_window_t test_menu = {
    menu_testOptions, 0, "TEST MENU      ", 0,
    MENU_WINDOW_SIZE, 0, TEST_WINDOW_LEN, 25,
    0, 0, 0, 20,
    {0, 0, 0, 0, 0},
    {
        {0}
    }, 0
};

/************************************************************************/
uint8_t fun_case = 0;
unsigned char set_speed(void *ptr) {

    switch (fun_case) {
        case 0:
            Timer_Stop(&led1_timer);
            Gpio_PinWrite(&led1, GPIO_LOW);
            fun_case++;
            break;
        case 1:
            if (muObj.key == 'U') {
                led_blink_speed++;
            } else if (muObj.key == 'D') {
                if (led_blink_speed)
                    led_blink_speed--;
            } else if (muObj.key == 'E') {
                fun_case++;
            }
            if (led_blink_speed > 1000)
                led_blink_speed = 0;
            sprintf((char *) muObj.out, "SET SPEED : \n%dms\n", led_blink_speed);
            break;
        case 2:
            sprintf((char *) muObj.out, "CURR SPEED : \n%dms\n", led_blink_speed);
            Timer_Start(&led1_timer, led_blink_speed, TIMER_RESTART_AFTER_COMPLETED);
            _delay_ms(1000);
            fun_case = 0;
            return 1;
    }


    if (muObj.key == 'C') {
        fun_case = 0;
        return 1;
    }
    return 0;
}

unsigned char set_pwm(void *ptr) {

    sprintf((char *) muObj.out, "SET PWM\nFUNCTION EXEC\n");

    if (muObj.key == 'C') {
        return 1;
    }
    return 0;
}
menu_window_opt_t menu_userOptions[] = {
    { .opt_heading_ptr = "SET SPEED",
        .type = MENU_TYP_FUN,
        .ptr = &set_speed,
        .params = &muObj,
        .next_menu = 0,
        .ret_val = RETURN_TO_MAIN_MENU},

    { .opt_heading_ptr = "SET PWM",
        .type = MENU_TYP_FUN,
        .ptr = &set_pwm,
        .params = &muObj,
        .next_menu = 0,
        .ret_val = RETURN_TO_MAIN_MENU},
};
#define USER_WINDOW_LEN sizeof(menu_userOptions)/sizeof(menu_window_opt_t)
menu_window_t user_menu = {
    menu_userOptions, 0, "USER MENU", 0,
    MENU_WINDOW_SIZE, 0, USER_WINDOW_LEN, 25,
    0, 0, 0, 20,
    {0, 0, 0, 0, 0},
    {
        {0}
    }, 0
};
/********************************************************************************************/

unsigned char fact_reset(void *ptr) {

    sprintf((char *) muObj.out, "FACTORY RESET\nFUNCTION EXEC\n");

    if (muObj.key == 'C') {
        return 1;
    }
    return 0;
}

unsigned char fact_restore(void *ptr) {

    sprintf((char *) muObj.out, "FACTORY RESTOR\nFUNCTRION EXEC");

    if (muObj.key == 'C') {
        return 1;
    }
    return 0;
}
menu_window_opt_t menu_factOptions[] = {
    { .opt_heading_ptr = "RESET",
        .type = MENU_TYP_FUN,
        .ptr = &fact_reset,
        .params = &muObj,
        .next_menu = 0,
        .ret_val = RETURN_TO_MAIN_MENU,},

    { .opt_heading_ptr = "RESTORE",
        .type = MENU_TYP_FUN,
        .ptr = &fact_restore,
        .params = &muObj,
        .next_menu = 0,
        .ret_val = RETURN_TO_MAIN_MENU,},
};
#define FACT_WINDOW_LEN sizeof(menu_factOptions)/sizeof(menu_window_opt_t)
menu_window_t factory_menu = {
    menu_factOptions, 0, "FATCORY MENU", 0,
    MENU_WINDOW_SIZE, 0, FACT_WINDOW_LEN, 25,
    0, 0, 0, 20,
    {0, 0, 0, 0, 0},
    {
        {0}
    }, 0
};

unsigned char disp_version(void *ptr) {

    menu_t *muPtr = (menu_t *) ptr;

    memcpy(muPtr->out, "SOFT VERSION\nV1.02\nLCD VERSION\nV0.02\n", strlen("SOFT VERSION\nV1.02\nLCD VERSION\nV0.02\n"));

    if (muPtr->key == 'C')
        return 1;

    return 0;
}
menu_window_opt_t my_windowOp[] = {
    { .opt_heading_ptr = "TEST",
        .type = MENU_TYP_MENU,
        .ptr = 0,
        .params = 0,
        .next_menu = &test_menu,
        .ret_val = RETURN_TO_DEFAULT_SCREEN},

    { .opt_heading_ptr = "USER",
        .type = MENU_TYP_MENU,
        .ptr = 0,
        .params = 0,
        .next_menu = &user_menu,
        .ret_val = RETURN_TO_DEFAULT_SCREEN},

    { .opt_heading_ptr = "FACTORY",
        .type = MENU_TYP_MENU,
        .ptr = 0,
        .params = 0,
        .next_menu = &factory_menu,
        .ret_val = RETURN_TO_DEFAULT_SCREEN},

    { .opt_heading_ptr = "VERSION",
        .type = MENU_TYP_FUN,
        .ptr = &disp_version,
        .params = &muObj,
        .next_menu = 0,
        .ret_val = RETURN_TO_DEFAULT_SCREEN},
};

#define MAIN_WINDOW_LEN sizeof(my_windowOp)/sizeof(menu_window_opt_t)

menu_window_t mainwindow = {
    my_windowOp, 0, "MAIN MENU", 0,
    MENU_WINDOW_SIZE, 0, MAIN_WINDOW_LEN, 25,
    0, 0, 0, 20,
    {0, 0, 0, 0, 0},
    { {0}}, 0
};

int main() {

    uTmr_Init();

    Lcd_Initialize(&lcdObj);

    Gpio_PinConfig(&buttonBack, GPIO_IN, GPIO_LOW);
    Gpio_PinConfig(&buttonDown, GPIO_IN, GPIO_LOW);
    Gpio_PinConfig(&buttonUp, GPIO_IN, GPIO_LOW);
    Gpio_PinConfig(&buttonEnter, GPIO_IN, GPIO_LOW);
    Gpio_PinConfig(&led1, GPIO_OUT, GPIO_LOW);
	
    Timer_Start(&led1_timer, led_blink_speed, TIMER_RESTART_AFTER_COMPLETED);
    Menu_Initialize(&muObj);

    muObj.window = &mainwindow;

    Uart_Initialize(9600);

    while (1) {

        uint8_t key = Uart_GetKey() | getKey();

        if (Timer_IsCompleted(&led1_timer)) {
            Gpio_PinToggle(&led1);
        }

        if (!Menu_Task(&muObj, key)) {

            Lcd_DefaultScreen(&lcdObj);

        } else {

            if (memcmp(muObj.out, muObj.prev_out, sizeof (muObj.prev_out))) {
                                Uart_WriteStr((const char *) muObj.out);
                memcpy(muObj.prev_out, muObj.out, sizeof (muObj.prev_out));
                Lcd_MenuScreen(&lcdObj, (char *) muObj.out);
            }

        }
        Lcd_Task(&lcdObj);
    }

    return 0;
}
