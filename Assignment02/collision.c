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

#include "plasmaBolt.h"
#include "fallingObjects.h"

// Uses pixel level collision to check if two objects have collided
// Returns 1 if there is collision
int check_collision(
    int x0,
    int y0,
    int w0,
    int h0,
    char pixels0[],
    int x1,
    int y1,
    int w1,
    int h1,
    char pixels1[]
) {
for (int j = x0; j < w0 + x0; j++) {
    for (int i = y0; i < h0 + y0; i++) {
        if (
            j >= x1 &&
            j < x1 + w1 &&
            i >= y1 &&
            i < y1 + h1 &&
            pixels1[ (j - x1) + (i - y1) * w1 ] != ' ' &&
            pixels0[ (j - x0) + (i - y0) * w0 ] != ' ') 
            {      
                return 1;
            } 
    }
}
            return 0;
}

// Calls collided function to specifically check if any asteroid has collided
// with any plasma bolt
// Returns 1 if collision is found
int asteroid_collision(int asteroid_num) {
    for (int i = 0; i < get_max_plasma_bolt(); i++) {
        int collided = check_collision(
            get_plasma_x(i),
            get_plasma_y(i),
            get_plasma_bolt_size(),
            get_plasma_bolt_size(),
            get_plasma_array(),
            get_asteroid_x(asteroid_num),
            get_asteroid_y(asteroid_num),
            get_asteroid_size(),
            get_asteroid_size(),
            get_asteroid_array()
        );

        if (collided) {
            set_plasma_bolt_y(i, -50);
            return 1;
        }

    }

    return 0;
}

