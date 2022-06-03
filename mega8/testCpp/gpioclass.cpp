/*
 * gpio.cpp
 *
 * Created: 06-05-2022 17:30:43
 *  Author: HP
 */ 
#include "GpioClass.h"

 GpioClass::GpioClass()
 : port(0),pin(0),direction(OUTPUT),state(LOW)
 {
	 
 }
 
 GpioClass::GpioClass(unsigned char p,unsigned char n)
 : port(p),pin(n),direction(OUTPUT),state(LOW)
 {
	 setDirection((GpioDirection_t)direction);
	 setState((GpioState_t)state);
 }

 GpioClass::GpioClass(unsigned char p,unsigned char n,GpioDirection_t d)
 : port(p),pin(n),direction(d),state(LOW)
 {
	 setDirection((GpioDirection_t)direction);
	 setState((GpioState_t)state);
 }

 GpioClass::~GpioClass() {
	 setState(LOW);
	 setDirection(INPUT);
 }
 void GpioClass::setPort(unsigned char p)
 {
	 port = p;
 }


 void GpioClass::setPin(unsigned char n)
 {
	 pin = n;
 }

 void GpioClass::setDirection(GpioDirection_t d)
 {
	 
	 unsigned char GSfrRegAddr =  GpioPortSfrAddress[port][GPIO_DIRECTION_REG];
	 unsigned char regValue = _SFR_IO8(GSfrRegAddr);
	 
	 regValue &= ~(1 << pin);
	 regValue |= (d << pin);
	 _SFR_IO8(GSfrRegAddr) = regValue;
	 direction = (regValue & (1 << pin));
 }

 void GpioClass::setState(GpioState_t s) {
	 
	 unsigned char GSfrRegAddr =  GpioPortSfrAddress[port][GPIO_OUTPUT_REG];
	 unsigned char regValue = _SFR_IO8(GSfrRegAddr);
	 regValue &= ~(1 << pin);
	 regValue |= (s << pin);
	 _SFR_IO8(GSfrRegAddr) = regValue;
	 
	 state = (regValue & (1 << pin)) ? 1:0;
	 
 }

 GpioClass::GpioState_t GpioClass::getState() {
	 
	 unsigned char GSfrRegAddr =  GpioPortSfrAddress[port][GPIO_INPUT_REG];
	 unsigned char regValue = _SFR_IO8(GSfrRegAddr);
	 
	 state = (regValue & (1 << pin)) ? 1:0;
	 
	 return (GpioState_t)state;
 }

 void GpioClass::toggleState() {
	 
	 GpioState_t cState = getState();
	 
	 if(cState == HIGH)
	 cState = LOW;
	 else
	 cState = HIGH;
	 
	 setState(cState);
 }