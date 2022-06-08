/*
 * main.c
 *
 * Created: 4/27/2022 1:47:53 PM
 *  Author: Richa
 */ 

#include <xc.h>

#include "common_utils.h"
#include "gpio_drv.h"
#include "rs232_ifc.h"
#include "rs485_ifc.h"
#include "sab82532.h"

gpio_obj_t pb02 = {
	GPIO_PORT_B,
	GPIO_PIN_2,
	GPIO_LVL_LOW
};

int main(void)
{
	RS232_Initialize(9600);
	
	GPIO_PinConfig(&pb02,GPIO_DIR_OUT,GPIO_LVL_LOW);
	
	SAB82532_Initialize(&sab82532Obj);

	while(1)
	{
		printf("0x%x VAL = 0x%x \n",SAB_STAR,SAB82532_ReadReg(&sab82532Obj,SAB_STAR));
		_delay_ms(1000);
	}
	
	return 0;
}