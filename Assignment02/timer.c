#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "lcd.h"
#include "cpu_speed.h"
#include "graphics.h"
#include "macros.h"
#include "cab202_adc.h"
#include "lcd_model.h"
#include "ascii_font.h"
#include "usb_serial.h"

// Set global variables to be used within timer.c
uint32_t over_flow_count = 0;
double elapsed_time;
int minutes;
int seconds;

// Set up a timer to be used to track the elapsed time of the game
void setup_timer() {
    TCCR1A = 0;
    TCCR1B = 0;
    TIMSK1 = 1;
    sei();
}

// Set up an interrupt service routine
ISR(TIMER1_OVF_vect) {
    over_flow_count++;
}


// Returns the current time elapsed during the game
double get_current_time() {
    return (over_flow_count * 65536.0 + TCNT1) * 256.0 / 8000000.0;
}

// Formats the current time into minutes and seconds
void time_elapsed() {
    elapsed_time = get_current_time();
    minutes = (int)elapsed_time / 60;
    seconds = (int)elapsed_time % 60;
}

// Returns the time formatted to minutes
int get_minutes() {
    return minutes;
}

// Returns the time formatted to seconds
int get_seconds() {
    return seconds;
}
