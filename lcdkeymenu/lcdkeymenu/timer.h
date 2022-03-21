/* 
 * File:   timer.h
 * Author: Bhura Malik
 *
 * Created on March 3, 2022, 5:09 PM
 */

#ifndef TIMER_H
#define	TIMER_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdlib.h>
#define F_CPU 1000000UL
#include <util/delay.h>
    typedef enum {
        TIMER_STOP_AFTER_COMPLETED,
        TIMER_RESTART_AFTER_COMPLETED
    } timer_action_t;
    
    typedef struct uTimerStruct {
        uint16_t id;
        uint16_t period;

        struct {
            uint8_t action : 1;
            uint8_t completed : 1;
            uint8_t start : 1;
        };
    } timer_t;

    typedef struct uTimerList {
        timer_t *ut;
        uint16_t rp;
        struct uTimerList *next;
    } timer_list_t;


    uint16_t FindFreeTimer(void);
    void Timer_TickEvent(void);
    void Timer_Start(timer_t *value, double time, uint8_t action);
    void Timer_Stop(timer_t *value);
    uint8_t Timer_IsStarted(timer_t *value);
    uint8_t Timer_IsCompleted(timer_t *value);
    void uTmr_Init();

#ifdef	__cplusplus
}
#endif

#endif	/* TIMER_H */

