/*
 * timer.h
 *
 * Created: 29-04-2022 17:27:26
 *  Author: HP
 */ 


#ifndef TIMER_H_
#define TIMER_H_

#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>

typedef enum {
	TIMER_STOPED,
	TIMER_STARTED,
	TIMER_COMPLETED
	}timer_action_t;
	
typedef enum {
	
	TIMER_SINGLE_SHOT,
	
	TIMER_MUTLI_SHOT
	
}timer_type_t;
	
typedef struct {
	
	unsigned short period;
	
	unsigned char id;
	
	struct  
	{
		unsigned char start:1;
		unsigned char action:1;
		unsigned char completed:1;
		unsigned char :5;
	};
}timer_obj_t;

typedef struct timer_obj_list{
    timer_obj_t *userTimer;
    unsigned short running_period;
	struct timer_obj_list *next;
}timer_obj_list_t;
	typedef timer_obj_list_t * TimerObjListHandle_t;
void TIMER_Initialize(void);

void TIMER_Add(timer_obj_t *);
void TIMER_Remove(timer_obj_t *);

void TIMER_Start(timer_obj_t *,unsigned short ,timer_type_t );
void TIMER_Stop(timer_obj_t *);

timer_action_t TIMER_IsCompleted(timer_obj_t *);
timer_action_t TIMER_IsStarted(timer_obj_t *);

#endif /* TIMER_H_ */