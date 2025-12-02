#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/power.h>
#include <util/atomic.h>

#include "include/millis.h"
#include "include/led_driver.hpp"
#include "include/button_driver.hpp"
#include "include/random_seed.hpp"

int main(void) {
    // Necessary to for counting time 
    sei(); 
    millis_init();

    // Enables the arduino to use more random numbers
    setup_seed();

    // Handle buttons as a list of buttons
    button_handle buttons[] = {
        button_handle(&DDRB, &PORTB, &PINB, PB5),
        button_handle(&DDRB, &PORTB, &PINB, PB4),
        button_handle(&DDRB, &PORTB, &PINB, PB3),
        button_handle(&DDRB, &PORTB, &PINB, PB2)
    };
    
    // Handle leds as a list of leds
    led_handle leds[] = {
        led_handle(&DDRB, &PORTB, &PINB, PB0),
        led_handle(&DDRD, &PORTD, &PIND, PD7),
        led_handle(&DDRD, &PORTD, &PIND, PD6),
        led_handle(&DDRD, &PORTD, &PIND, PD5)
    };
    
    while(1) {
        // Check if the buttons has been pressed - in that case toggle the led
        for (uint8_t i = 0; i < (sizeof(leds) / sizeof(leds[0])); i++) {
            if (buttons[i].is_pressed()) leds[i].toggle();
        }

        // Non-blocking delay from millis library
        millis_wait_ms(20);
    }

    return 0;
}