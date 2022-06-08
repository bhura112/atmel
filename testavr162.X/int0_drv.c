#include "int0_drv.h"


ISR(INT0_vect) {
    
    printf("GIS  : %c",sabObj.ygis);
    printf("ISR0 : %c",sabObj.ygis);
    printf("ISR1 : %c",sabObj.ygis);
   
    printf(nwline);
}

void INT0_Initialize(void)
{
    MCUCR |=  (1 << ISC01) | (1 << ISC00);
    
    GICR |= (1 << INT0);
}
