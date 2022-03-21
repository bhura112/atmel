#include "menu.h"
#include "lcd.h"
extern lcd_t lcdObj;

const uint8_t invalid_pass[] = "INVALID PASSWORD\nTry AGAIN";

void Menu_Initialize(menu_t *menu) {

    memset(menu->out, 0, sizeof (menu->out));
    memset(menu->prev_out, 0, sizeof (menu->prev_out));
}

uint8_t Menu_GetString(menu_t *menu, uint8_t key, uint8_t *buffer) {

    switch (menu->str->state) {
        case 0:
            menu->str->state++;

            break;
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
    }
    return 0;
}

uint8_t Menu_GetPassword(menu_t *menu, uint8_t key, uint8_t *password) {

    static uint8_t pass_state = 0;

        switch (pass_state) {
            case 0:
            //            menu->str = malloc(sizeof *menu->str);
            //            if (menu->str) {
            //
            //                pass_state++;
            //            }
                break;
            case 1:

            //            return Menu_GetString(menu, key, password);
            break;
      }

    return 0;
}

unsigned char Menu_SelectOpt(menu_t *menu) {

    unsigned char temp_line_num = 0;

    menu_window_t *curr_window = menu->window;

    switch (curr_window->opt_state) {
        case 0:
            memset(menu->out, 0, sizeof (menu->out));

            menu->out_size = sprintf((char *) menu->out, "%s\n", curr_window->heading_ptr);

            for (temp_line_num = 0; temp_line_num < curr_window->total_size; temp_line_num++) {

                if (curr_window->hlight_line_num == temp_line_num) {
                    menu->out_size += sprintf((char *) (menu->out + menu->out_size), ">%d. %s\n",
                        curr_window->window_st_num + temp_line_num,
                        curr_window->opt[curr_window->window_st_num + temp_line_num].opt_heading_ptr
                            );
                }
                else
                    menu->out_size += sprintf((char *) (menu->out + menu->out_size), "%d. %s\n",
                        curr_window->window_st_num + temp_line_num,
                        curr_window->opt[curr_window->window_st_num + temp_line_num].opt_heading_ptr
                        );

            }

            memset(menu->out + menu->out_size, 0, sizeof (menu->out) - menu->out_size);

             curr_window->opt_state++;
            break;
        case 1:
            if (menu->key == 'D') {

                curr_window->hlight_line_num++;
                if (curr_window->hlight_line_num >= curr_window->total_size)
                    curr_window->hlight_line_num = 0;

                if (curr_window->hlight_line_num == curr_window->window_size) {
                    curr_window->window_st_num++;
                    curr_window->hlight_line_num--;
                    if (curr_window->window_st_num > (curr_window->total_size - curr_window->window_size)) {
                        curr_window->window_st_num = 0;
                        curr_window->hlight_line_num = 0;
                    }
                }
                curr_window->opt_state = 0;
            } else if (menu->key == 'U') {
                if (curr_window->hlight_line_num == 0) {

                    if (curr_window->window_st_num) {
                        curr_window->window_st_num--;
                        curr_window->hlight_line_num = 0;
                    } else {
                        int8_t st_num = curr_window->total_size - curr_window->window_size;
                        if (st_num < 0)
                            st_num = 0;
                        curr_window->window_st_num = st_num;
                        curr_window->hlight_line_num = curr_window->total_size - 1;
                    }
                } else {
                    curr_window->hlight_line_num--;
                }
                curr_window->opt_state = 0;

            } else if (menu->key == 'E') {

                curr_window->curr_list_sel = curr_window->hlight_line_num + curr_window->window_st_num;
                curr_window->opt_state = 0;
                return 1;

            } else if (menu->key == 'C') {

                curr_window->flags.bits.cancelled = 1;
                curr_window->opt_state = 0;
                return 1;
            }
            break;
    }

    return 0;
}

void Menu_Flush(menu_window_t *window) {
    window->curr_list_sel = 0;
    window->hlight_line_num = 0;
    window->window_st_num = 0;
    window->flags.bits.cancelled = 0;
    window->state = 0;
    window->opt_state = 0;
}
uint8_t Menu_Task(menu_t *menu, uint8_t key) {

    menu->key = key;

    menu_window_t *c_window = menu->window;

    if (c_window)
        menu->constwindow = c_window;

    switch (c_window->state) {

        case MENU_IDLE:
            if (menu->key == 'E') {
                c_window->state++;
                // Timer_Start(&menu->timeout, 1000, TIMER_STOP_AFTER_COMPLETED);
            }
            break;

        case MENU_PROTECTION:

            if (c_window) {

                if (c_window->password[0] != 0) {
                    uint8_t usrpassword[4];
                    uint8_t ret = Menu_GetPassword(menu, key, usrpassword);

                    if (ret) {
                        if (!memcmp(usrpassword, c_window->password, 4))
                            c_window->state++;
                        else
                            memcpy(menu->out, invalid_pass, sizeof (invalid_pass));
                    } else
                        c_window->state++;
                }

                // Timer_Start(&menu->timeout, 5000, TIMER_STOP_AFTER_COMPLETED);
                c_window->state++;

            } else {
                //memcpy(menu->out, "INVALID MENU\r\n", strlen("INVALID MENU\r\n"));
                //if (Timer_IsCompleted(&menu->timeout))
                   c_window->state = 0;
            }
            break;
        case MENU_OPEN:
            c_window->state++;
            break;

        case MENU_SELECT_OPT:

            if (Menu_SelectOpt(menu)) {

                memset(menu->out, 0, sizeof (menu->out));

                if (c_window->flags.bits.cancelled || c_window->flags.bits.timeout) {
                    c_window->flags.bits.cancelled = 0;
                    c_window->flags.bits.timeout = 0;
                    if (c_window->prev_window) {
                        menu->window = menu->window->prev_window;
                        menu->window->state = MENU_SELECT_OPT;
                    } else {
                        c_window = menu->constwindow;
                        Menu_Flush(c_window);
                        return 1;
                    }
                }
                c_window->state++;
                memset(menu->out, 0, sizeof (menu->out));
            }
            break;

        case MENU_EXEC_OPT:
            if (c_window->opt[c_window->curr_list_sel].type) {
                menu_window_t *h_window = c_window;
                c_window = c_window->opt[c_window->curr_list_sel].next_menu;
                c_window->prev_window = h_window;
                Menu_Flush(c_window);
                menu->window = c_window;
                c_window->state = 1;
            } else {
                if (c_window->opt[c_window->curr_list_sel].ptr(c_window->opt[c_window->curr_list_sel].params)) {
                    memset(menu->out, 0, sizeof (menu->out));
                    switch (c_window->opt[c_window->curr_list_sel].ret_val) {
                        case RETURN_TO_SAME_MENU:
                            c_window->state = 2;
                            break;
                        case RETURN_TO_MAIN_MENU:
                            Menu_Flush(c_window);
                            c_window = menu->constwindow;
                            c_window->state = 2;
                            break;
                        case RETURN_TO_DEFAULT_SCREEN:
                            Menu_Flush(c_window);
                            c_window = menu->constwindow;
                            c_window->state = 0;
                            break;
                    }
                }
            }
            break;

    }

    return c_window->state;
}
