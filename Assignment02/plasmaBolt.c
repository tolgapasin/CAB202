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

#include "drawToScreen.h"
#include "starShip.h"
#include "timer.h"

// Define constant variables to be used within plasmaBolt.c
#define MAX_PLASMA_BOLT 50
#define PLASMA_BOLT_SIZE 2

// Set global variables to be used within plasmaBolt.c
int plasma_count = 0;
int plasma_bolt_x[MAX_PLASMA_BOLT], plasma_bolt_y[MAX_PLASMA_BOLT];
double shoot_time;

// Set char array to be used when drawing an asteroid to the screen
char * plasma_bolt = {
    "##"
    "##"
};

// Sets the coordinates for all available plasma bolts off screen
void setup_plasma_bolt() {
    for(int i = 0; i < MAX_PLASMA_BOLT; i++) {
        plasma_bolt_x[i] = 0;
        plasma_bolt_y[i] = -50;
    }
}

// Draws all available plasma bolts to the screen
void draw_plasma_bolt() {
    for(int i = 0; i < MAX_PLASMA_BOLT; i++) {
        draw_shape(plasma_bolt_x[i], plasma_bolt_y[i], PLASMA_BOLT_SIZE, PLASMA_BOLT_SIZE, plasma_bolt, 0);
    }
}

// Updates the position for each plasma bolt
// Plasma bolts are constantly travelling upwards
// If plasma bolt is to be shot, sets coordinates to just above the starfighter
// Only shoots if max amount of plasma bolts is not on screen
void update_plasma_bolt(char charFromComp) {
    for (int i = 0; i < MAX_PLASMA_BOLT; i++) {
            plasma_bolt_y[i]--;
    }

    if ((BIT_IS_SET(PIND, 1) || charFromComp == 'w') && (get_current_time() >= (shoot_time + 0.2))) {
        shoot_time = get_current_time();
        if (plasma_bolt_y[plasma_count] < 0) {
            plasma_bolt_x[plasma_count] = get_star_ship_x() + 2;
            plasma_bolt_y[plasma_count] = get_star_ship_y() - 2;
            plasma_count++;
        } else {
            plasma_bolt_y[plasma_count] = -5;
            plasma_count = 0;
        }
    }

}

// Returns the x coordinate for a plasma bolt
int get_plasma_x(int plasma_num) {
    return plasma_bolt_x[plasma_num];
}

// Returns the y coordinate for a plasma bolt
int get_plasma_y(int plasma_num) {
    return plasma_bolt_y[plasma_num];
}

// Returns the size of a plasma bolt
int get_plasma_bolt_size() {
    return PLASMA_BOLT_SIZE;
}

// Returns the char array used to draw a plasma bolt
char * get_plasma_array() {
    return plasma_bolt;
}

// Returns the maximum am0unt of plasma bolts
int get_max_plasma_bolt() {
    return MAX_PLASMA_BOLT;
}

// Sets the y coordinate of a plasma bolt
void set_plasma_bolt_y(int plasma_num, int value) {
    plasma_bolt_y[plasma_num] = value;
}