#include "../include/game_gui.hpp"
#include "../include/led_driver.hpp"

void startup_light_sequence(led_handle *leds, int num_leds, uint16_t delay_ms)
{
    for (int i = 0; i < num_leds; i++)
    {
        leds[i].turn_on();
        uint32_t start = millis_get();
        while (millis_get() - start < delay_ms)
        {
            // wait
        }
        leds[i].turn_off();
    }
}

void new_game(led_handle * leds, int num_leds, uint16_t delay_ms) {
     for (int i = 0; i < num_leds; i++)
    {
        leds[i].turn_on();
        uint32_t start = millis_get();
        while (millis_get() - start < delay_ms)
        {
            // wait
        }
        leds[i].turn_off();
    }
}

void correct_answer(led_handle * leds, int num_leds, uint16_t delay_ms) {
        {
            uint32_t start = millis_get();
            leds[1].turn_on();
            leds[3].turn_on();
            while (millis_get() - start < delay_ms)
            {
                // wait
            }
            leds[1].turn_off();
            leds[3].turn_off();
        }

    }