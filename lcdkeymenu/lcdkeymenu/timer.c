

#include "timer.h"

static timer_list_t *uTmrLst;
#define TICKS_VAL(R_TIME,PRESCALLER) (uint8_t)(255 - (8000000UL*R_TIME) / PRESCALLER)
ISR(TIMER0_OVF_vect) {

    Timer_TickEvent();
    TCNT0 = TICKS_VAL(0.001, 1024);
    TIFR &= ~(1 << TOV0);
}

uint16_t FindFreeTimer(void) {
    timer_list_t *pTimer = uTmrLst;
    while (pTimer) {
        if (pTimer->next) {
            if ((pTimer->next->ut->id - pTimer->ut->id) > 2)
                return (pTimer->ut->id + 1);
            else {
                pTimer = pTimer->next;
            }
        } else
            return (pTimer->ut->id + 1);
    }
    return (1);
}

void Timer_Add(timer_t *value) {
    timer_list_t *pTimer;
    timer_list_t *pNewTimer = 0;

    /* Look for the timer ? if already exists */
    value->id = FindFreeTimer();
    value->start = 0;
    value->completed = 0;
    pTimer = uTmrLst;
    /* Create a new timer */
    pNewTimer = malloc(sizeof (timer_list_t));
    if (pNewTimer != 0) {
        pNewTimer->ut = value;
        pNewTimer->rp = 0;
        pNewTimer->next = 0;
        /* Check if the list is empty */
        if (pTimer == 0) {
            /* Store the address of this timer as a first element in the list */
            uTmrLst = pNewTimer;
        } else {
            while (pTimer->ut->id != (pNewTimer->ut->id - 1))
                pTimer = pTimer->next;
            /*Add the new timer to the end of the list */
            pNewTimer->next = pTimer->next;
            pTimer->next = pNewTimer;
            /*Add the new timer to the end of the list */
            //pTimer = pNewTimer;
        }
    }
}

/**
 * use this function to remove timer
 * @param value Timer_Obj_Typedef object pointer
 * @return TIMER_STATUS_Typedef
 */
void Timer_Remove(timer_t *value) {

    timer_list_t *pTimer, *prevTimer;

    /* Update the timers */
    pTimer = uTmrLst;
    prevTimer = pTimer;
    while (pTimer != 0) {
        if (pTimer->ut->id == value->id) {
            prevTimer->next = pTimer->next;
            value->id = 0;
            free(pTimer);
            if (uTmrLst == pTimer)
                uTmrLst = pTimer->next;
            break;
        } else {
            /* Move to the next timer in the list */
            prevTimer = pTimer;
            pTimer = pTimer->next;
        }
    }
}

void Timer_Start(timer_t *value, double time, uint8_t action) {

    timer_list_t *pTimer;


    if (value->id == 0) {

        Timer_Add(value);
    }

    pTimer = uTmrLst;

    while (pTimer != 0) {
        if (pTimer->ut->id == value->id) {
            pTimer->ut->period = time;
            pTimer->ut->action = action;
            pTimer->ut->start = 1;
            if (!pTimer->ut->period)
                pTimer->ut->completed = 1;
            else
                pTimer->ut->completed = 0;
            pTimer->rp = pTimer->ut->period;
            return;
        } else {
            /* Move to the next timer in the list */
            pTimer = pTimer->next;
        }
    }
}

void Timer_Stop(timer_t *value) {

    value->start = 0;
    value->completed = 0;
}

uint8_t Timer_IsStarted(timer_t *value) {


    return (value->start);
}

uint8_t Timer_IsCompleted(timer_t *value) {

    if (value->completed) {
        value->completed = 0;
        return (1);
    }
    return 0;
}

void Timer_TickEvent(void) {

    timer_list_t *pTimer;

    /* Update the timers */
    pTimer = uTmrLst;

    while (pTimer != 0) {

        if (pTimer->rp != 0) {

            if (pTimer->ut->start == 1) {
                /* Decrement the timer period */
                pTimer->rp--;
            }

            /* Check if the timer has reached zero */
            if (pTimer->rp == 0) {
                if (pTimer->ut->action == TIMER_STOP_AFTER_COMPLETED) {
                    pTimer->ut->start = 0;
                } else
                    pTimer->rp = pTimer->ut->period;
                pTimer->ut->completed = 1;
            }
        }
        /* Move to the next timer in the list */
        pTimer = pTimer->next;
    }
}

void uTmr_Init() {

    sei();
    TIMSK = (1 << TOIE0);
    TCNT0 = TICKS_VAL(0.001, 1024);
    TCCR0 = 5;
}
