/*
 * seven-seg.c
 *
 * Created: 21-03-2022 12:00:38
 * Author : Apaul
 */ 

#include <avr/io.h>


#include "seg.h"

segment_t sev_seg = {0};
segment_t sev_seg_2 = {0};
	
int main(void)
{
	//int x =35;
	
   segment_config(&sev_seg,
                             5,     //8,                 // digits
							 
                             SEG_PIN(PORT_A,PIN_0),  // control pins
                             SEG_PIN(PORT_A,PIN_1),
							 SEG_PIN(PORT_A,PIN_2),
							 SEG_PIN(PORT_A,PIN_3),
							 SEG_PIN(PORT_A,PIN_4), 
							 /*SEG_PIN(PORT_A,PIN_5),
							 SEG_PIN(PORT_A,PIN_6),
							 SEG_PIN(PORT_A,PIN_7),*/
							 
							 SEG_PIN(PORT_B,PIN_0),  // data pins
							 SEG_PIN(PORT_B,PIN_1),
							 SEG_PIN(PORT_B,PIN_2),
							 SEG_PIN(PORT_B,PIN_3),
							 SEG_PIN(PORT_B,PIN_4),
							 SEG_PIN(PORT_B,PIN_5),
							 SEG_PIN(PORT_B,PIN_6),
							 SEG_PIN(PORT_B,PIN_7), 
							 
							 SEG_ANODE); //type
							 
      segment_config(&sev_seg_2,
                             6,                 // digits
							 
                             SEG_PIN(PORT_E,PIN_0),  // control pins
                             SEG_PIN(PORT_E,PIN_1),
							 SEG_PIN(PORT_E,PIN_2),
							 SEG_PIN(PORT_E,PIN_3),
							 SEG_PIN(PORT_E,PIN_4), 
							 SEG_PIN(PORT_E,PIN_5),
							 
							 SEG_PIN(PORT_D,PIN_0),  // data pins
							 SEG_PIN(PORT_D,PIN_1),
							 SEG_PIN(PORT_D,PIN_2),
							 SEG_PIN(PORT_D,PIN_3),
							 SEG_PIN(PORT_D,PIN_4),
							 SEG_PIN(PORT_D,PIN_5),
							 SEG_PIN(PORT_D,PIN_6),
							 SEG_PIN(PORT_D,PIN_7), 
							 
							 SEG_CATHODE); //type
							 
    while (1) 
    {
		
				
				segment_writeChar(&sev_seg_2,0,'S');
				
				segment_writeChar(&sev_seg_2,1,9);
				segment_writeChar(&sev_seg_2,2,4);
				
		segment_writeChar(&sev_seg,0,'T');
		
		segment_writeChar(&sev_seg,1,4);
        segment_writeChar(&sev_seg,2,1);
		
		segment_writeChar(&sev_seg,3,'\'');
		segment_writeChar(&sev_seg,4,'C');
		
		

		
		
		
    }
}

