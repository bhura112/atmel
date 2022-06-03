/*
 * LcdClass.h
 *
 * Created: 06-05-2022 18:31:24
 *  Author: HP
 */ 


#ifndef LCDCLASS_H_
#define LCDCLASS_H_

#include "GpioClass.h"

class LcdClass
{
public:
	LcdClass();
	~LcdClass();
private:
	GpioClass rs_pin;
	GpioClass rw_pin;
	GpioClass en_pin;
	GpioClass bklt_pin;
	GpioClass databus[8];
};


#endif /* LCDCLASS_H_ */