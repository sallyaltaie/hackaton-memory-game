#include "../include/button_driver.hpp"

#include "avr/interrupt.h"
#include "../include/millis.h"

// ------------------- STATIC VARIABLES AND FUNCTIONS -------------------
button_handle* button_handle::instances[MAX_BUTTONS] = { nullptr };
uint8_t button_handle::instance_count = 0;

void button_handle::dispatch_isr() {
    for (uint8_t i = 0; i < instance_count; i++) {
        if (instances[i] != nullptr) {
            instances[i]->handle_interrupt();
        }
    }
}


// ------------------- BUTTON_HANDLE MEMBERS -------------------
bool button_handle::get_state() {
    return !(*pin_reg & pin_mask);
}

void button_handle::debounced_button_click() {
    auto now = millis_get();

    if (now - last_pressed > DEBOUNCE_MS) {
        if (get_state()) {
            pressed = true;
        }
        last_pressed = now;
    }
}

void button_handle::handle_interrupt() {
    debounced_button_click();
}

void button_handle::enable_interrupt() {
    if (pin_reg == &PINB) {
        PCICR |= (1 << PCIE0);
        PCMSK0 |= pin_mask;
    } else if (pin_reg == &PINC) {
        PCICR |= (1 << PCIE1);
        PCMSK1 |= pin_mask;
    } else if (pin_reg == &PIND) {
        PCICR |= (1 << PCIE2);
        PCMSK2 |= pin_mask;
    }
    
    instances[instance_count++] = this;
}

button_handle::button_handle(volatile uint8_t* ddr, volatile uint8_t* port, volatile uint8_t* pin_reg, uint8_t pin) 
: ddr(ddr), port(port), pin_reg(pin_reg), pin_mask(1 << pin), pressed(false), last_pressed(0)
{
    *ddr &= ~pin_mask;
    *port |= pin_mask;

    if (instance_count < MAX_BUTTONS) enable_interrupt();
}

bool button_handle::is_pressed() {
    if (pressed) {
        pressed = false;
        return true;
    }
    return false;
}

button_handle::~button_handle() {
    *port &= ~pin_mask;

    if (pin_reg == &PINB) {
        PCMSK0 &= ~pin_mask;
    } else if (pin_reg == &PINC) {
        PCMSK1 &= ~pin_mask;
    } else if (pin_reg == &PIND) {
        PCMSK2 &= ~pin_mask;
    }
}

void button_handle::flush() {
    pressed = false;
}

ISR(PCINT0_vect) { button_handle::dispatch_isr(); }
ISR(PCINT1_vect) { button_handle::dispatch_isr(); }
ISR(PCINT2_vect) { button_handle::dispatch_isr(); }