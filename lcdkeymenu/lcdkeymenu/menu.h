/* 
 * File:   menu.h
 * Author: Bhura Malik
 *
 * Created on March 4, 2022, 1:55 PM
 */

#ifndef MENU_H
#define	MENU_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "timer.h"
#define MENU_STR_MAX_BUFFER 16
#define MENU_WINDOW_SIZE 3
    typedef enum {
        MENU_TYP_FUN,
        MENU_TYP_MENU
    } menu_type_t;

    typedef enum {
        RETURN_TO_SAME_MENU = 1,
        RETURN_TO_MAIN_MENU,
        RETURN_TO_DEFAULT_SCREEN
    } menu_return_t;
    typedef enum {
        MENU_IDLE,
        MENU_PROTECTION,
        MENU_OPEN,
        MENU_SELECT_OPT,
        MENU_EXEC_OPT
    } menu_state_t;

    typedef struct {
        uint8_t state;
        uint8_t buffer[MENU_STR_MAX_BUFFER];
    } menu_str_t;

    typedef struct menu_window_option_struct_t {
        const char *opt_heading_ptr;
        menu_type_t type;
        unsigned char (*ptr) (void *);
        void *params;
        struct menu_window_struct_t *next_menu;
        uint8_t ret_val;
    } menu_window_opt_t;

    typedef union {

        struct {
            uint8_t cancelled : 1;
            uint8_t timeout : 1;
            uint8_t pwd_protected : 1;
            uint8_t get_txt : 1;
uint8_t:
            4;
        } bits;
        uint8_t u8;
    } menu_flags_t;

    typedef struct menu_window_struct_t {
        menu_window_opt_t *opt;

        struct menu_window_struct_t *prev_window;

        const char *heading_ptr;

        uint8_t window_st_num;

        uint8_t window_size;

        uint8_t hlight_line_num;

        uint8_t total_size;

        uint8_t font_size;

        uint8_t font_index_ptr;

        uint8_t curr_list_sel;

        uint8_t state;

        uint8_t timeout;

        uint8_t password[5];
        menu_flags_t flags;
        uint8_t opt_state;
    } menu_window_t;
    
    typedef struct menu_struct_t {
        menu_window_t *window;
        menu_window_t *constwindow;
        menu_str_t *str;
        uint8_t out[64];
        uint8_t prev_out[64];
        uint16_t out_size;
        uint8_t key;
    } menu_t;

    void Menu_Initialize(menu_t *menu);

    uint8_t Menu_Task(menu_t *menu, uint8_t key);

#ifdef	__cplusplus
}
#endif

#endif	/* MENU_H */

