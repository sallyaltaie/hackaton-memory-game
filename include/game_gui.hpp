#ifndef GAME_GRAPHICAL_USER_INTERFACE_HPP_
#define GAME_GRAPHICAL_USER_INTERFACE_HPP_

#include "led_driver.hpp"

    void startup_light_sequence(led_handle* leds, int num_leds, uint16_t delay_ms);
    void correct_answer(led_handle* leds, int num_leds, uint16_t delay_ms);


#endif