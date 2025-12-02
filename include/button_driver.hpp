#ifndef MEMORY_BUTTON_DRIVER_HPP_
#define MEMORY_BUTTON_DRIVER_HPP_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "avr/io.h"

#define DEBOUNCE_MS 200

/* 
Handle for controlling inputs through buttons on AVR ATMega328p. The constructor
automatically sets up interrupts based on the port and pin passed as argument.
Exposes the following functions:
*  - is_pressed() returns the current state of the button
*  - flush() resetting the button to not-pressed state

Note: After pressing a button, its state will be pressed until either read by
is_pressed() or reseted by flush()
*/
class button_handle {
private:
    volatile uint8_t* ddr;
    volatile uint8_t* port;
    volatile uint8_t* pin_reg;

    // Mask used for setting and unsetting bits
    uint8_t pin_mask;

    // The current state of the button
    bool pressed;

    // Debounce timer
    unsigned long last_pressed;

    // static registration for ISR
    static constexpr uint8_t MAX_BUTTONS = 8;
    static button_handle* instances[MAX_BUTTONS];
    static uint8_t instance_count;

    bool get_state();
    void debounced_button_click();
    void enable_interrupt();
    void handle_interrupt();

public:
    /*
    Sets up the pin properly to handle a button.

    @param *ddr address (&) to the Data Direction Register for the correct port
    @param *port address (&) to the Port Register for the correct port
    @param *pin_reg address (&) to the Pin Register for the correct port
    @param pin correct pin position in the port register.

    Example:
    
    button_handle red_button(&DDRB, &PORTB, &PINB, PB5);
    */
    button_handle(volatile uint8_t* ddr, volatile uint8_t* port, volatile uint8_t* pin_reg, uint8_t pin);

    /* 
    Checks the current state of the button. If it has been pressed,
    automatically resets the state to false.

    @return true if it has been pressed, false if it hasn't.
    */
    bool is_pressed();

    /* 
    Flushes the current input from the button.
    */
    void flush();
    
    /* 
    Helper function for dispatching ISR for our buttons. Not to be used outside of the class!
    */
    static void dispatch_isr();
    ~button_handle();
};

#endif