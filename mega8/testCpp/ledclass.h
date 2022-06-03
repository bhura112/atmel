/*
 * ledclass.h
 *
 * Created: 06-05-2022 17:49:43
 *  Author: HP
 */ 


#ifndef LEDCLASS_H_
#define LEDCLASS_H_

#include "GpioClass.h"


class LedClass : public GpioClass {
public:
	LedClass();
	LedClass(unsigned char ,unsigned char);
	~LedClass();
	void set();
	void clear();
	void toggle();
private:

};



#endif /* LEDCLASS_H_ */