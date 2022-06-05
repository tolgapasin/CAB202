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
#include "fallingObjects.h"
#include "serial.h"
#include "timer.h"
#include "fallingObjects.h"

/** The following code has been adapted from the elapsed time AMS exercise **/
// A simple buffer that holds data to be drawn to screen
char buffer[500];

// Allows the data type double to be drawn to screen like a String
void draw_double(uint8_t x, uint8_t y, double value, colour_t colour) {
	snprintf(buffer, sizeof(buffer), "%f", value);
	draw_string(x, y, buffer, colour);
}

// Allows the data type int to be drawn to screen like a String
void draw_int(uint8_t x, uint8_t y, int value, colour_t colour) {
	snprintf(buffer, sizeof(buffer), "%d", value);
	draw_string(x, y, buffer, colour);
}

/***************************************************************************/

// Draws a char array to screen
void draw_shape( int left, int top, int width, int height, char bitmap[], int space_is_transparent) {
    for ( int j = 0; j < height; j++ ) {
     	for ( int i = 0; i < width; i++ ) {

			if ( bitmap[i+j * width] != ' ') {
				draw_pixel(left+i, top+j, bitmap[i+j*width]);
			} else if ( !space_is_transparent ) {
				draw_pixel( left+i, top+j, ' ');
			}

    	}
 	}
}

// Draws a dashed line to screen
// Can draw horizontal and vertical lines
void draw_dashed_line(int x1, int y1, int x2, int y2, colour_t colour) {
    if ( x1 == x2 ) {
        int i = y1;

		while (i <= y2) {
        	draw_pixel(x1, i, colour);
            i+=2;
		}

	} else if ( y1 == y2 ) {
        int i = x1;
		
        while (i <= x2) {
			    draw_pixel(i, y1, colour);
                i+=2;
		}

	}
}

// Sends the game status over usb serial to the computer hosting the teensy
void send_status_serial() {
	snprintf(buffer, sizeof(buffer), "Time: %02d:%02d\n\rLives: %d\n\rScore: %d\n\rAsteroids: %d\n\rBoulders: %d\n\rFragments: %d\n\rPlasma bolts: %d\n\rTurret aim: %d\n\rSpeed of game: %d\n\n\r", get_minutes(), get_seconds(), get_lives(), get_score(), get_asteroid_num(), 0, 0, 0, 0, 0);
	send_over_serial(buffer);
}

// Sends the controls of the game to the computer hosting the teensy
void send_controls_serial() {
	snprintf(buffer, sizeof(buffer), "Controls:\n\r'a' – move spaceship left\n\r'd' – move spaceship right\n\r'w' – fire plasma bolts\n\r's' – send/display status\n\r'r' – start/reset\n\r'p' – pause\n\r'q' – quit\n\r't' – set aim (-60 to 60)\n\r'm' – set speed (0 to 10)\n\r'l' – set life\n\r'g' – set score\n\r'?' – print controls\n\r'h' – spaceship to coord\n\r'j' – asteroid to coord\n\r'k' – boulder to coord\n\r'i' – fragment to coord\n\n\r");
	send_over_serial(buffer);
}

