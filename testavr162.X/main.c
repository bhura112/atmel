/*
 * main.c
 *
 * Created: 4/27/2022 1:47:53 PM
 *  Author: HP
 */ 

#include <xc.h>

#include "common_utils.h"
#include "gpio_drv.h"
#include "rs232_ifc.h"
#include "rs485_ifc.h"
#include "sab82532.h"
#include "int0_drv.h"



void Sys_Initialize( void );

int main(void)
{
    Sys_Initialize();
    
    INT0_Initialize();
    
    RS232_Initialize(9600);
   
    if (!SAB82532_xMemInitiailze(&sabObj,9600) )
    {
       
         printf("\r\nsab >");
    }

    uint8_t rchr = 0;
    
	while(1)
	{		

       CLI_Interface();
       
        if( SAB82532_xMemGetCChar(&sabObj,&rchr) )
        {
           if(rchr)
           {
               printf("RCHAR : %c \r\n",rchr);
           }
        }
       
	}
	
	return 0;
}

void Sys_Initialize( void )
{
    sei();
    
    DDRB |= (1 << PB0) | (1 << PB1);
    
    PORTB |= (1 << PB0);
    _delay_ms(100);
    
    PORTB &= ~(1 << PB0);
    _delay_ms(100);
    
    
}