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
#include "usb_serial.h"
#include "lcd_model.h"
#include "ascii_font.h"

#include "fallingObjects.h"
#include "drawToScreen.h"

// Define constant variables to be used within starShip.c
#define STAR_SHIP_SIZE 7

// Set global variables to be used within starShip.c
int star_ship_x, star_ship_y;
int movingRight = 0;
int movingLeft = 1;
int stop = 0;

// Setup a binary array to be used when drawing the starfighter to the screen
uint8_t star_ship_original[7] = {
    0b00010000,
    0b00010000,
    0b00010000,
    0b00010000,
    0b01111100,
    0b11111110,
    0b10101010,
};

// Setup another array to assist in drawing the starfighter
uint8_t star_ship_direct[7];

// Setup the starfighter using direct writing
void setup_star_ship(void) {
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            uint8_t bit_val = BIT_VALUE(star_ship_original[j], (7 - i));
            WRITE_BIT(star_ship_direct[i], j, bit_val);
        }
    }

    star_ship_x = 38;
    star_ship_y = 40;
}

// Draw the starfighter to screen using direct writing
void draw_star_ship(void) {
    LCD_CMD(lcd_set_function, lcd_instr_basic | lcd_addr_horizontal);
    LCD_CMD(lcd_set_x_addr, star_ship_x);
    LCD_CMD(lcd_set_y_addr, star_ship_y / 7);

    for (int i = 0; i < 7; i++) {
        LCD_DATA(star_ship_direct[i]);
    }

}

// Update the position of the starfighter
void update_star_ship(char charFromComp) {
    if (BIT_IS_SET(PIND, 0) || charFromComp == 'd') {
        if (movingLeft) {
            movingLeft = 0;
            stop = 1;
        } else if (!stop) {
            movingRight = 1;
        }
        stop = 0;
    }

    if (BIT_IS_SET(PINB, 1) || charFromComp == 'a') {
        if (movingRight) {
            movingRight = 0;
            stop = 1;
        } else if (!stop) {
            movingLeft = 1;
        }
        stop = 0;
    }

    if (star_ship_x == 0) {
        movingLeft = 0;
    } else if (movingLeft) {
        star_ship_x--;
    }

    if (star_ship_x == 76) {
        movingRight = 0;
    } else if (movingRight) {
        star_ship_x++;
    }

}

// Return the starfighters current x coordinate
int get_star_ship_x() {
    return star_ship_x;
}

// Return the starfighters current y coordinate
int get_star_ship_y() {
    return star_ship_y;
}

// Set the starfighters current x coordinate
void set_star_ship_x(int x) {
    star_ship_x = x;
}

// Set the starfighters current y coordinate
void set_star_ship_y(int y) {
    star_ship_y = y;
}






