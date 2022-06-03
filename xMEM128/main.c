/*
 * xMEM128.c
 *
 * Created: 01-06-2022 17:58:36
 * Author : HP
 */ 

#include <avr/io.h>
#include <stdlib.h>
#include <string.h>
#define F_CPU 1000000UL
#include <util/delay.h>


#define OFFSET 0x2000

void XMem_Initialize( void )
{

 MCUCR = (1 << SRE);
// XMCRA = (1 << SRL2) | (1 << SRW00) | (1 << SRW11);
 SFIOR = 0;
}

void XMem_Write(volatile uint16_t *addr,uint8_t val)
{
	//(*(uint16_t *)(addr)) = val;	
	*((uint8_t *)(addr)) = val;
}

void XMem_WriteString(volatile uint16_t *addr,uint8_t *str)
{
	uint16_t memcount = 0;
	while (*str)
	{
		XMem_Write((addr + memcount),*str);
		memcount++;
		str++;
	}
	
}

uint8_t XMem_Read(uint16_t *addr)
{
    uint16_t xval = 0;
	xval = (*(uint8_t *)(addr));
	return xval;
}
 
int main(void)
{
 
 XMem_Initialize();
 
 DDRD = 0xFF;
 PORTD = 0x00;

  
 XMem_WriteString ((uint16_t *) (OFFSET), (uint8_t *)"ABC 123 *#%");
 
	_delay_ms(1000);
	
	while (1)
	{
		
		for (int i = 0; i < 1000; i++)
		{
			PORTD = XMem_Read((uint16_t *) (OFFSET + i));
			_delay_ms(1000);
		}
	

	}
}

