#include <stdint.h>
#include <stdio.h>
#include <avr/io.h> 
#include <avr/interrupt.h>
#include <util/delay.h>
#include <cpu_speed.h>
#include <graphics.h>
#include <macros.h>

#include "lcd_model.h"

// Set global variables to be used within debounce.c
volatile uint8_t counter = 0;
volatile uint8_t pressed = 0;
uint8_t prev_state = 0;

// Setup a timer to be used for debouncing
void setup_debounce() {
	TCCR3A = 0;
    TCCR3B = 4;
	TIMSK3 = 1;
	sei();
	SET_INPUT(DDRF, 5);
}

// Set up an interrupt service routine
ISR(TIMER3_OVF_vect) {
		counter = (counter << 1);
		uint8_t mask = 0b00111111;
		counter = counter & mask;
		counter = counter | (BIT_VALUE(PINF, 5) << 0);

		if (counter == mask) {
			pressed = 1;
		} else if (counter == 0) {
			pressed = 0;
		}

}

// Return the status of the pressed variable
uint8_t get_pressed() {
    return pressed;
}

// Return the status of the previous state variable
uint8_t get_prev_state() {
    return prev_state;
}

// Set the status of the previous state variable
void set_prev_state(uint8_t state) {
    prev_state = state;
}
