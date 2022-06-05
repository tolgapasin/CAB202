#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <cab202_graphics.h>
#include <cab202_timers.h>
#include "vacuum.h"
#include "hud.h"

// Define the vacuum dimension
#define VACUUM_DIMENSION 9
// Define the vacuums speed
#define VACUUM_SPEED 0.2

// Define the vacuums step per time slice
const double step = VACUUM_SPEED;

// Define the x, y, delta x and delta y coordinates of the vacuum
double vx, vy, vdx, vdy; 

// Define delta values used to return the vacuum to the base
double rdx, rdy;

// Define the direction that the vacuum should travel in
double vacuum_dir = 90;

// Define the load weight of the vacuum to 0
int load_weight = 0;

// Define the vacuums docks char array
char * vacuum =
"  @@@@@  "
" @-----@ "
"@-------@"
"@-------@"
"@-------@"
"@-------@"
"@-------@"
" @-----@ "
"  @@@@@  "
;

// Draws a char array to a specified location
void draw_pixels ( 
    int left, 
    int top, 
    int width, 
    int height, 
    char bitmap[], 
    bool space_is_transparent
) {
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++ ) {
            if ( bitmap[i+j * width] != ' ') {
                draw_char(left+i, top+j, bitmap[i+j*width]);
            } else if ( !space_is_transparent ) {
                draw_char( left+i, top+j, ' ');
            }
        }
    }
}

// Uses draw_pixels to draw vacuum at its pre-defined x and y
// coordinates
void draw_vacuum() {
    int screen_w, screen_h;
    get_screen_size(&screen_w, &screen_h);
    draw_pixels(vx, vy, VACUUM_DIMENSION, VACUUM_DIMENSION, vacuum, true);
}

// Setups the x and y coordinates of the vacuum
void setup_vacuum() {
    int screen_w, screen_h;
    get_screen_size(&screen_w, &screen_h);
    vx = (screen_w-VACUUM_DIMENSION)/2;
    vy = (screen_h-VACUUM_DIMENSION)/2;
    vdx = step * cos(vacuum_dir);
    vdy = step * sin(vacuum_dir);
}

// Updatest the vacuum position by one step in its current direction,
// if it hits a wall it bounces off of it at a random angle between
// 30 and 60. It will go left or right by a random choice
void update_vacuum_pos() {
    int new_x = round(vx + vdx) - VACUUM_DIMENSION / 2; 
    int new_y = round(vy + vdy) - VACUUM_DIMENSION / 2;
    bool bounced = false;
    int choice = (rand() % (2 + 1 - 1) + 1);

    if (choice == 1) {
        vacuum_dir += (rand() % (60 + 1 - 30) + 30);
        vacuum_dir = (int)vacuum_dir % 360;
    } else if (choice == 2) {
        vacuum_dir -= (rand() % (60 + 1 - 30) + 30) ;
        vacuum_dir = (int)vacuum_dir % 360;
    }

    if(new_x +3 == 0 || new_x + VACUUM_DIMENSION +4 == screen_width()) {
        vdx = step * cos(vacuum_dir);
        bounced = true;
    }

    if (new_y -1 == 0 || new_y + VACUUM_DIMENSION +6 == screen_height()) {
        vdy = step * sin(vacuum_dir);
        bounced = true;
    }

    if (!bounced) {
        vx += vdx;
        vy += vdy;
    }
}

// Sets the delta values used to return the vacuum to the dock
void setup_return_to_base() {
    double t1 = get_dockx() - vx;
    double t2 = get_docky() - vy;
    double delta_val = sqrt(t1 * t1 + t2 * t2);
    rdx = t1 * 0.1 / delta_val;
    rdy = t2 * 0.1 / delta_val;
}

// Sets the vacuum in the direction of the charging dock
// until it is adjacent. It then waits there to charge and
// drop off rubbish. Then it continues normal movement
void return_to_base() {
    vx += round(rdx);
    vy += round(rdy);
}

// Formats the updated direction to be used in the status bar
double update_direction() {
    double direction = atan2(vdy, vdx);
    direction = (int)((direction + M_PI) * 360.0 / (2.0 * M_PI) + 180) %360;
    return direction;
}

// Getter functions
double get_vacuum_vx() {
    return vx;
}

double get_vacuum_vy() {
    return vy;
}

double get_vacuum_vdx() {
    return vdx;
}

double get_vacuum_vdy() {
    return vdy;
}

double get_vacuum_dir() {
    return vacuum_dir;
}

double get_formatted_dir() {
    return update_direction();
}

double get_vacuum_step() {
    return step;
}

int get_vacuum_dimension() {
    return VACUUM_DIMENSION;
}

int get_load_weight() {
    return load_weight;
}

double get_vacuum_speed() {
    return VACUUM_SPEED;
}

char * get_vacuum_array() {
    return vacuum;
}

// Setter functions
void set_vacuum_vx(double x) {
    vx = x;
}

void set_vacuum_vy(double y) {
    vy = y;
}

void set_vacuum_vdx(double dx) {
    vdx = dx;
}

void set_vacuum_vdy(double dy) {
    vdy = dy;
}

void set_vacuum_weight(int weight) {
    load_weight = weight;
}

void set_vacuum_dir(double direction) {
    vacuum_dir = direction;
}
