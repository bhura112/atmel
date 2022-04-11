#include <avr/io.h>
#include <avr/boot.h>



#include "uart.h"

int main(void)
{
    Uart_Initialize(9600);	
	
	while (1)
	{
		Uart_Task();
	}
}
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  