#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <cab202_graphics.h>
#include <cab202_timers.h>
#include "vacuum.h"
#include "hud.h"
#include "trash.h"

// Checks the collision between two objects
// Uses the objects x and y coordinates,
// width and height and char array
bool check_collision(
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
                return true;
            } 
    }
}
            return false;
}

// Uses check_collision to check if the vacuum has collided with the dock
bool collided_dock() {
    int screen_w, screen_h;
    get_screen_size(&screen_w, &screen_h);
    int dock_x = screen_w / 2 - get_dock_width() / 2;
    int dock_y = 5;

    if (
        check_collision(
            get_vacuum_vx(),
            get_vacuum_vy(),
            get_vacuum_dimension(),
            get_vacuum_dimension(),
            get_vacuum_array(),
            dock_x,
            dock_y,
            get_dock_width(),
            get_dock_height(),
            get_dock_array() )
    ) {
        return true;
    }

    return false;
}

// Bounces the vacuum off the dock at a angle between 30 and 60 degrees
// if they have collided
void bounce_dock() {
    if (collided_dock()) {
        set_vacuum_vdx(get_vacuum_step() * cos(get_vacuum_dir()));
        set_vacuum_vdy(get_vacuum_step() * sin(get_vacuum_dir()));
    }
}

// Checks if the vacuum has collided with a piece of trash
// Trash x and y values are being used for testing purposes
bool collided_trash() {
    if (
        check_collision(
            get_vacuum_vx(),
            get_vacuum_vy(),
            get_vacuum_dimension(),
            get_vacuum_dimension(),
            get_vacuum_array(),
            70,
            20,
            get_trash_width(),
            get_trash_height(),
            get_trash_array()

        )
    ) {
        return true;
    }
    return false;
 }

// Deletes the amount piece of trash from the screen and increments
// the load weight of the vacuum by 20g
void pickup_trash() {
    if ( collided_trash() ) {
        set_vacuum_weight(get_load_weight() + 20);
        show_screen();
    }
}


