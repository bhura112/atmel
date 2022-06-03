/*
 * ledclass.cpp
 *
 * Created: 06-05-2022 17:49:58
 *  Author: HP
 */ 
#include "ledclass.h"


LedClass::LedClass()
: GpioClass() {
	
}

LedClass::LedClass(unsigned char p,unsigned char n)
: GpioClass(p,n,OUTPUT) {
	
}

LedClass::~LedClass()
{

}

void LedClass::set() {
	setState(HIGH);
}
void LedClass::clear() {
	setState(LOW);
}
void LedClass::toggle() {
	toggleState();
}

