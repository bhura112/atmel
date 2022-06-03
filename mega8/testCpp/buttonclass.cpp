/*
 * buttonclass.cpp
 *
 * Created: 06-05-2022 18:08:27
 *  Author: HP
 */ 
#include "ButtonClass.h"

ButtonClass::ButtonClass()
: GpioClass() {
	
}

ButtonClass::ButtonClass(unsigned char p,unsigned char n)
: GpioClass(p,n,INPUT) {
	
}

ButtonClass::~ButtonClass()
{

}

ButtonClass::ButtonState_t ButtonClass::read() {
	
	return getState();
}
