// Holds the necessary functions and variables used to setup
// debouncing within the program
#pragma once

void setup_debounce();

uint8_t get_pressed();
uint8_t get_prev_state();

void set_prev_state(uint8_t state);