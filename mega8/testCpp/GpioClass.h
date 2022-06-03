/*
 * gpio.h
 *
 * Created: 06-05-2022 17:31:04
 *  Author: HP
 */ 


#ifndef GPIO_H_
#define GPIO_H_

#include "bsp.h"

class GpioClass{

	public:
	
	typedef bool GpioState_t;
	typedef bool GpioDirection_t;
	

	
	GpioClass();
	
	GpioClass(unsigned char p ,unsigned char n );
	
	GpioClass(unsigned char p ,unsigned char n,GpioDirection_t d);
	
	void setPort(unsigned char p);
	
	void setPin(unsigned char n);
	
	void setDirection(GpioDirection_t);
	
	void setState(GpioState_t);
	
	GpioState_t getState();
	
	void toggleState();
	
	~GpioClass();
	
	private:
	unsigned char port;
	
	unsigned char pin;
	
	struct
	{
		unsigned char direction:1;
		volatile unsigned char state:1;
	};
};


#endif /* GPIO_H_ */