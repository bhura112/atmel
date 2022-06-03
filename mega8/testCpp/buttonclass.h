/*
 * buttonclass.h
 *
 * Created: 06-05-2022 18:08:47
 *  Author: HP
 */ 


#ifndef BUTTONCLASS_H_
#define BUTTONCLASS_H_


#include "GpioClass.h"


class ButtonClass : public GpioClass {
	public:
	typedef  GpioClass::GpioState_t  ButtonState_t;
	ButtonClass();
	ButtonClass(unsigned char ,unsigned char);
	~ButtonClass();
	ButtonState_t read();
	private:

};


#endif /* BUTTONCLASS_H_ */