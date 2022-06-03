/*
 * timer.c
 *
 * Created: 29-04-2022 17:27:50
 *  Author: HP
 */ 
#include "timer.h"


static TimerObjListHandle_t timerObj_List;

void TIMER_Initialize(void) {
	
}

static unsigned char TIMER_FindFree(void) {
	
	TimerObjListHandle_t listPtr = timerObj_List;

	while (listPtr)
	{
		if(listPtr->next) 
		{
			if( (listPtr->next->userTimer->id - listPtr->userTimer->id) > 2)
			{
				return (listPtr->userTimer->id + 1);
			}else
				listPtr = listPtr->next;
		}else 
          return (listPtr->userTimer->id + 1);		
	}
	return 1;
}

void TIMER_Add(timer_obj_t *userTimer) {
	
	TimerObjListHandle_t listPtr = timerObj_List;
	TimerObjListHandle_t newListNode = 0;
	
	if (userTimer == 0)
	{
		return;
	}
	
	userTimer->id = TIMER_FindFree();
	userTimer->start     = 0;
	userTimer->completed = 0;
	
	newListNode = malloc(sizeof *newListNode);
	
	if (newListNode)
	{
		newListNode->userTimer = userTimer;
		newListNode->next = 0;
		newListNode->running_period = 0;
		
		if(listPtr == 0) {
			listPtr = newListNode;
		}else {
			
			while (listPtr->next->userTimer->id != (listPtr->userTimer->id -1))
				listPtr = listPtr->next;
			
			newListNode->next = listPtr->next;
			   
			
		}
	}
}

void TIMER_Remove(timer_obj_t *userTimer) {
	
}

void TIMER_Start(timer_obj_t *userTimer,unsigned short timeout,timer_type_t type) {
	
}
void TIMER_Stop(timer_obj_t *userTimer) {
	
}

timer_action_t TIMER_IsCompleted(timer_obj_t *userTimer) {
	timer_action_t action = TIMER_STOPED;
	
	return action;
}
timer_action_t TIMER_IsStarted(timer_obj_t *userTimer) {
	
	timer_action_t action = TIMER_STOPED;
	
	
	
	return action;
}