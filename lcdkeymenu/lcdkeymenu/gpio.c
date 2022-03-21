#include "gpio.h"



static volatile uint8_t *iomap[][3] = {
    {&DDRA, &PORTA, &PINA},
    {&DDRB, &PORTB, &PINB},
    {&DDRC, &PORTC, &PINC},
    {&DDRD, &PORTB, &PIND},
    {&DDRE, &PORTC, &PINE},
};

void Gpio_PinConfig(gpio_t *io, gpio_dir_t dir, gpio_state_t state) {

    *iomap[io->_port][0] |= (dir << io->_pin);

    Gpio_PinWrite(io, state);

}

void Gpio_PinWrite(gpio_t *io, gpio_state_t state) {

    uint8_t pval = *iomap[io->_port][1];

    pval &= ~(1 << io->_pin);
    pval |= (state << io->_pin);

    *iomap[io->_port][1] = pval;
}

uint8_t Gpio_PinRead(gpio_t *io) {
    return (*iomap[io->_port][2] & (1 << io->_pin));
}

void Gpio_PinToggle(gpio_t *io) {
    Gpio_PinWrite(io, !Gpio_PinRead(io));
}