#ifndef MEMORY_LED_DRIVER_HPP_
#define MEMORY_LED_DRIVER_HPP_

#include <stdio.h>
#include <stdint.h>

#include "avr/io.h"

#define DDR DDRB

/* 
Handle for controlling LEDs on AVR ATMega328p. Exposes the following functions:
*  - turn_on()
*  - turn_off()
*  - toggle()
*/
class led_handle {
private:
    volatile uint8_t* ddr;
    volatile uint8_t* port;
    volatile uint8_t* pin_reg;

    // Mask used to set the correct bits
    uint8_t pin_mask;

public:
    /*
    Sets up the pin properly to handle an LED.

    @param *ddr address (&) to the Data Direction Register for the correct port
    @param *port address (&) to the Port Register for the correct port
    @param *pin_reg address (&) to the Pin Register for the correct port
    @param pin correct pin position in the port register.
    
    Example:
    
    led_handle red_led(&DDRB, &PORTB, &PINB, PB0);
    */
    led_handle(volatile uint8_t* ddr, volatile uint8_t* port, volatile uint8_t* pin_reg, uint8_t pin);
    void turn_on();
    void turn_off();
    void toggle();
    ~led_handle();
};

#endif