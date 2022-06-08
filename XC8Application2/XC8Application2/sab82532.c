/*
 * sab82532.c
 *
 * Created: 01-06-2022 10:09:31
 *  Author: HP
 */ 
#include "sab82532.h"


		
sab82532_obj_t sab82532Obj = {
	
	.rd_ds = RD_DS_LINE,
	.wrr_rw = WR_R_RW_LINE,
	.ale = ALE_LINE, 
  
	.line = {
		.a0 = ADDR_DATA_LINE0,
		.a1 = ADDR_DATA_LINE1,
		.a2 = ADDR_DATA_LINE2,
		.a3 = ADDR_DATA_LINE3,
		.a4 = ADDR_DATA_LINE4,
		.a5 = ADDR_DATA_LINE5,
		.a6 = ADDR_DATA_LINE6,
		.a7 = ADDR_DATA_LINE7
	}
  
};

void SAB82532_LinConfig(sab82532_obj_t *sab,bool dir,bool state)
{
	
	GPIO_PinConfig(&sab->line.a0,dir,state);
	GPIO_PinConfig(&sab->line.a1,dir,state);
	GPIO_PinConfig(&sab->line.a2,dir,state);
	GPIO_PinConfig(&sab->line.a3,dir,state);
	GPIO_PinConfig(&sab->line.a4,dir,state);
	GPIO_PinConfig(&sab->line.a5,dir,state);
	GPIO_PinConfig(&sab->line.a6,dir,state);
	GPIO_PinConfig(&sab->line.a7,dir,state);
	
}
void SAB82532_Initialize( sab82532_obj_t *sab)
{
	GPIO_PinConfig(&sab->rd_ds,GPIO_DIR_OUT,GPIO_LVL_HIGH);
	GPIO_PinConfig(&sab->wrr_rw,GPIO_DIR_OUT,GPIO_LVL_HIGH);
	GPIO_PinConfig(&sab->ale,GPIO_DIR_OUT,GPIO_LVL_HIGH);
	
    SAB82532_LinConfig(sab,GPIO_DIR_OUT,GPIO_LVL_LOW);
}

void SAB82532_WritePins(sab82532_obj_t *sab,uint8_t b)
{
	addr_data_reg_t regv = (addr_data_reg_t)b;
	
	GPIO_PinSet(&sab->line.a0 , regv.b.b0);
	GPIO_PinSet(&sab->line.a1 , regv.b.b1);
	GPIO_PinSet(&sab->line.a2 , regv.b.b2);
	GPIO_PinSet(&sab->line.a3 , regv.b.b3);
	GPIO_PinSet(&sab->line.a4 , regv.b.b4);
	GPIO_PinSet(&sab->line.a5 , regv.b.b5);
	GPIO_PinSet(&sab->line.a6 , regv.b.b6);
	GPIO_PinSet(&sab->line.a7 , regv.b.b7);
	
}

uint8_t SAB82532_ReadPins(sab82532_obj_t *sab)
{
	addr_data_reg_t regv = {0};
	
	 regv.b.b0 = GPIO_PinGet(&sab->line.a0);
	 regv.b.b1 = GPIO_PinGet(&sab->line.a0);
	 regv.b.b2 = GPIO_PinGet(&sab->line.a0);
	 regv.b.b3 = GPIO_PinGet(&sab->line.a0);
	 regv.b.b4 = GPIO_PinGet(&sab->line.a0);
     regv.b.b5 = GPIO_PinGet(&sab->line.a0);
     regv.b.b6 = GPIO_PinGet(&sab->line.a0);
	 regv.b.b7 = GPIO_PinGet(&sab->line.a0);
	
	return regv.byte;
}




uint8_t SAB82532_ReadReg(sab82532_obj_t *sab,uint8_t reg)
{
	uint8_t regv = 0;
	
	SAB82532_LinConfig(sab,GPIO_DIR_OUT,GPIO_LVL_LOW);
	
	SAB82532_WritePins(sab,reg);
	
	GPIO_PinSet(&sab->rd_ds,GPIO_LVL_LOW);
	
	GPIO_PinSet(&sab->ale,GPIO_LVL_LOW);
	
	asm("nop");
	asm("nop");
	SAB82532_LinConfig(sab,GPIO_DIR_IN,GPIO_LVL_LOW);
	asm("nop");
	asm("nop");
	
	regv = SAB82532_ReadPins(sab);
	
	GPIO_PinSet(&sab->ale,GPIO_LVL_HIGH);
	
	GPIO_PinSet(&sab->rd_ds,GPIO_LVL_HIGH);
	
	return regv;
}

inline void SAB82532_TecWait(sab82532_obj_t *sab)
{
	int timeout = SAB82532_MAX_TEC_TIMEOUT;
	
	addr_data_reg_t regv = {0};
	
	do 
	{
		regv.byte = SAB82532_ReadReg(sab,SAB_STAR);
		asm("nop");
	} while ((regv.byte & SAB_STAR_TEC) && --timeout);
}

inline void SAB82532_CecWait(sab82532_obj_t *sab)
{
	int timeout = SAB82532_MAX_CEC_TIMEOUT;
	
	addr_data_reg_t regv = {0};
	
	do
	{
		regv.byte = SAB82532_ReadReg(sab,SAB_STAR);
		asm("nop");
	} while ((regv.byte & SAB_STAR_CEC) && --timeout);

}