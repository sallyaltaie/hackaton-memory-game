#include "../include/led_driver.hpp"

led_handle::led_handle(volatile uint8_t* ddr, volatile uint8_t* port, volatile uint8_t* pin_reg, uint8_t pin)
: ddr(ddr), port(port), pin_reg(pin_reg), pin_mask(1 << pin)
{
    *ddr |= pin_mask;
    *port &= ~pin_mask;
}

void led_handle::turn_on() {
    *port |= pin_mask;
}

void led_handle::turn_off() {
    *port &= ~pin_mask;
}

void led_handle::toggle() {
    *port ^= pin_mask;
}

led_handle::~led_handle() {
    *port &= ~pin_mask;
    *ddr &= ~pin_mask;
}