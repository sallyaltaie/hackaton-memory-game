#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/power.h>
#include <util/atomic.h>

#include "include/millis.h"
#include "include/led_driver.hpp"
#include "include/button_driver.hpp"
#include "include/random_seed.hpp"
#include "include/game_gui.hpp"

int main(void) {
    // Necessary to for counting time 
    sei(); 
    millis_init();

    // Enables the arduino to use more random numbers
    setup_seed();

led_handle leds[] = {
        led_handle(&DDRB, &PORTB, &PINB, PB0),
        led_handle(&DDRD, &PORTD, &PIND, PD7),
        led_handle(&DDRD, &PORTD, &PIND, PD6),
        led_handle(&DDRD, &PORTD, &PIND, PD5)
    };

    // Play start sequence once.
    while(1) {
        startup_light_sequence(leds, 4, 800);
        millis_wait_ms(1000);
        correct_answer(leds, 4, 800);
        break;
        
        // // Check if the buttons has been pressed - in that case toggle the led
        // for (uint8_t i = 0; i < (sizeof(leds) / sizeof(leds[0])); i++) {
        //     if (buttons[i].is_pressed()) leds[i].toggle();
        // }
        // // Exempel: blinka alla LEDs i sekvens
        // for (uint8_t i = 0; i < (sizeof(leds) / sizeof(leds[0])); i++) {
        //     leds[i].turn_on();
        //     millis_wait_ms(200);
        //     leds[i].turn_off();
        // }
        // millis_wait_ms(1000);

    //     leds[0].turn_on();
    //     millis_wait_ms(1000);
    //     leds[0].turn_off();
    //     millis_wait_ms(1000);
    // }

    return 0;
}

}