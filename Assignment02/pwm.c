#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "lcd.h"
#include "cpu_speed.h"
#include "graphics.h"
#include "macros.h"
#include "cab202_adc.h"
#include "lcd_model.h"
#include "ascii_font.h"
#include "usb_serial.h"

/** The following code has been adapted from the adc_pwm_backlight example code**/

// Define constant variables to be used within pwm.c
#define BIT(x) (1 << (x))
#define OVERFLOW_TOP (1023)
#define ADC_MAX (1023)

// Sets up a timer necessary for handling pwm functionality
void setup_pwm() {
	TC4H = OVERFLOW_TOP >> 8;
	OCR4C = OVERFLOW_TOP & 0xff;
	TCCR4A = BIT(COM4A1) | BIT(PWM4A);
	SET_BIT(DDRC, 7);
	TCCR4B = BIT(CS42) | BIT(CS41) | BIT(CS40);
	TCCR4D = 0;
}

// Sets the duty cycle for pwm
void set_duty_cycle(int duty_cycle) {
	TC4H = duty_cycle >> 8;
	OCR4A = duty_cycle & 0xff;
}

// Sets the level for pwm and applys it to the backlight of the teensy
void set_pwm_level(int level) {
    long left_adc = level;
	set_duty_cycle(ADC_MAX - left_adc);
}

/********************************************************************************/