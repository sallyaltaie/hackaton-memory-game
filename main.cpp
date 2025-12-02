#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/power.h>
#include <util/atomic.h>

#include "include/millis.h"
#include "include/led_driver.hpp"
#include "include/button_driver.hpp"
#include "include/random_seed.hpp"
#include "include/game_gui.hpp"

enum GameState {STARTUP, WAIT, CORRECT, WRONG, END};

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

    // Game result

    enum GameState { STARTUP, USER_INPUT, NEW_GAME, WAIT, CORRECT, END };
    GameState state = USER_INPUT;
    bool running = true;

    while(running) {

        switch(state) {
            case STARTUP:
                startup_light_sequence(leds, 4, 800);
                millis_wait_ms(1000);
                state = CORRECT;
                break;
            case NEW_GAME:
                new_game(leds, 4, 400);
                millis_wait_ms(1000);
            case CORRECT:
                correct_answer(leds, 4, 800);
                state = END;
                break;
            case END:
                running = false;
                break;
            case WAIT:
                // Put the code for incoming input from player (luddes code)
                break;
        }
    }

    return 0;
}
