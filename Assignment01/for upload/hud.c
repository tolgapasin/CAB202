#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <cab202_graphics.h>
#include <cab202_timers.h>
#include "hud.h"
#include "vacuum.h"
#include "trash.h"

// Define the charging docks dimensions
#define DOCK_WIDTH 9
#define DOCK_HEIGHT 3

// Define the charging docks x and y coordinate
double dock_x, dock_y;

// Define the charging docks char array
char * dock =
"#########"
"#########"
"#########"
;

// Draws the segmenting lines and strings that make up the status bar
void draw_status_bar(double vacuum_dir, int vacuum_battery, int seconds, int minutes, int vacuum_weight, int dust_amount, int slime_amount, int trash_amount) {
    int screen_w, screen_h;
    get_screen_size(&screen_w, &screen_h);
    const int chTop = '-';
    const int chSides = '|';
    const int intersect = '+';

    draw_line(0, 2, screen_w - 1, 2, chTop);
    draw_line(0, 4, screen_w - 1, 4, chTop);
    draw_line(screen_w / 3, 0, screen_w / 3, 4, chSides);
    draw_line(screen_w / 1.5, 0, screen_w / 1.5, 4, chSides);
    draw_char(0, 2, intersect);
    draw_char(0, 4, intersect);
    draw_char(screen_w / 3, 0, intersect);
    draw_char(screen_w / 1.5, 0, intersect);
    draw_char(screen_w / 3, 2, intersect);
    draw_char(screen_w / 1.5, 2, intersect);
    draw_char(screen_w / 3, 4, intersect);
    draw_char(screen_w / 1.5, 4, intersect);
    draw_char(screen_w - 1, 2, intersect);
    draw_char(screen_w - 1, 4, intersect);

    draw_string(2, 1, "Student #: n9737197");
    draw_formatted(screen_w / 3 + 2, 1, "Robot Direction: %f", vacuum_dir);
    draw_formatted(screen_w / 1.5 + 2, 1, "Battery Life: %d", vacuum_battery);
    draw_formatted(2, 3, "Time Elapsed: %02d:%02d", minutes, seconds);
    draw_formatted(screen_w / 3 + 2, 3, "Load Weight: %d", vacuum_weight);
    draw_formatted(screen_w / 1.5 + 2, 3, "Rubbish Available: %d, %d, %d", dust_amount, slime_amount, trash_amount);
}

// Draws the rest of the border
void draw_border() {
    int screen_w, screen_h;
    get_screen_size(&screen_w, &screen_h);
    const int chTop = '-';
    const int chSides = '|';
    const int intersect = '+';
    
    draw_line(0, 0, 0, screen_h - 3, chSides);
    draw_line(0, 0, screen_w - 1, 0, chTop);
    draw_line(0, screen_h - 3, screen_w - 1, screen_h - 3, chTop);
    draw_line(screen_w - 1, 0, screen_w - 1, screen_h - 3, chSides);
    draw_char(0, 0, intersect);
    draw_char(0, screen_h - 3, intersect);
    draw_char(screen_w - 1, 0, intersect);
    draw_char(screen_w - 1, screen_h - 3, intersect);
}

// Draws the charging dock
void draw_charging_dock() {
    int screen_w, screen_h;
    get_screen_size(&screen_w, &screen_h);
    dock_x = screen_w / 2 - DOCK_WIDTH / 2;
    dock_y = 5;
    draw_pixels( dock_x, dock_y, DOCK_WIDTH, DOCK_HEIGHT, dock, false);
}

// Getter functions
int get_dock_width(){
    return DOCK_WIDTH;
}

int get_dock_height(){
    return DOCK_HEIGHT;
}

char * get_dock_array() {
    return dock;
}

double get_dockx() {
    return dock_x;
}

double get_docky() {
     return dock_y;
}