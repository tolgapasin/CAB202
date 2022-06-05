#include <stdint.h>
#include <string.h>
#include <avr/io.h> 
#include <avr/interrupt.h>
#include <util/delay.h>
#include <cpu_speed.h>
#include <macros.h>
#include <graphics.h>
#include <stdio.h>
#include "usb_serial.h"

/** The following code has been adapted from the usb_serial_echo example code**/

// Define constant variables to be used within serial.c
#define FREQ 8000000.0
#define PRESCALE 256.0
#define TIMER_SCALE 256.0

// Set global variables to be used within serial.c
double interval = 0;

// Set up an interrupt service routine
ISR(TIMER0_OVF_vect) {
	interval += TIMER_SCALE * PRESCALE / FREQ;

	if ( interval >= 1.0 ) {
		interval = 0;
		PORTD ^= 1 << 6;
	}
}

// Connect teensy to the computer via usb serial
void setup_serial() {
    usb_init();

    while ( !usb_configured() ) {

    }

}

// Sends a message over usb serial from the teensy to the computer
void send_over_serial(char * message) {
	usb_serial_write((uint8_t *) message, strlen(message));
}

/******************************************************************************/