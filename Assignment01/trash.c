#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <cab202_graphics.h>
#include <cab202_timers.h>
#include "vacuum.h"
#include "helpers.h"

// Define constant variables
// Maximum amounts of each type of rubbish alllowed
#define MAX_DUST 1000
#define MAX_SLIME 10
#define MAX_TRASH 5

// Weight specification for each type of rubbish
#define DUST_WEIGHTT 1
#define SLIME_WEIGHT 5
#define TRASH_WEIGHT 20

// Dimensions of each type of rubbish
#define DUST_DIMENSION 1
#define SLIME_DIMENSION 5
#define TRASH_HEIGHT 6
#define TRASH_WIDTH 11

// Define global variables
// Amount of each type of rubbish specified by user
// Arrays to hold multiple x and y coordinates for each piece of rubbish
int dust_amount = 0;
int slime_amount = 0;
int trash_amount = 0;
double dx[MAX_DUST], dy[MAX_DUST], sx[MAX_SLIME], sy[MAX_SLIME], tx[MAX_TRASH], ty[MAX_TRASH];

// Define char arrays used to represent the different types of rubbish
char * dust =
"."
;
char * slime =
"~~~~~"
"~~~~~"
"~~~~~"
"~~~~~"
"~~~~~"
;
char * trash = 
"     &     "
"    &&&    "
"   &&&&&   "
"  &&&&&&&  "
" &&&&&&&&& "
"&&&&&&&&&&&"
;

// Sets up a single piece of dust at a random x and y coordinate
// Saves x and y coordinates in arrays to allow for more dust later
void setup_dust(int index) {
    int screen_w, screen_h;
    get_screen_size(&screen_w, &screen_h);
    dx[index] = 1 + DUST_DIMENSION / 2 + rand() % (screen_w - DUST_DIMENSION - 2);
    dy[index] = 7 + DUST_DIMENSION / 2 + rand() % (screen_h - DUST_DIMENSION - 2);
}

// Gets input from user to specify how much dust to produce
// Calls setup_dust for specified amount of times
// Checks if user inputs a negative number or more that the allowed max,
// and realocates amount to 0 if true
void setup_multiple_dust() {
    dust_amount = get_int("How much dust would you like?");

    if (dust_amount > MAX_DUST || dust_amount < 1) {
        dust_amount = 0;
    }

    for (int i = 0; i < dust_amount; i++) {
        setup_dust(i);
    }
}

// Sets up a single piece of slime at a random x and y coordinate
// Saves x and y coordinates in arrays to allow for more slime later
void setup_slime(int index) {
    int screen_w, screen_h;
    get_screen_size(&screen_w, &screen_h);
    sx[index] = 1 + SLIME_DIMENSION / 2 + rand() % (screen_w - SLIME_DIMENSION - 2);
    sy[index] = 7 + SLIME_DIMENSION / 2 + rand() % (screen_h - SLIME_DIMENSION - 2);
}

// Gets input from user to specify how much slime to produce
// Calls setup_slime for specified amount of times
// Checks if user inputs a negative number or more that the allowed max,
// and realocates amount to 0 if true
void setup_multiple_slime() {
    slime_amount = get_int("How much slime would you like?");

    if (slime_amount > MAX_SLIME || slime_amount < 1) {
        slime_amount = 0;
    }

    for (int i = 0; i < slime_amount; i++) {
        setup_slime(i);
    }
}

// Sets up a single piece of trash at a random x and y coordinate
// Saves x and y coordinates in arrays to allow for more trash later
void setup_trash(int index) {
    int screen_w, screen_h;
    get_screen_size(&screen_w, &screen_h);
    tx[index] = 1 + TRASH_WIDTH / 2 + rand() % (screen_w - TRASH_WIDTH - 2);
    ty[index] = 7 + TRASH_HEIGHT / 2 + rand() % (screen_h - TRASH_HEIGHT - 2);
}

// Gets input from user to specify how much trash to produce
// Calls setup_trash for specified amount of times
// Checks if user inputs a negative number or more that the allowed max,
// and realocates amount to 0 if true
void setup_multiple_trash() {
    trash_amount = get_int("How much trash would you like?");

    if (trash_amount > MAX_TRASH || trash_amount < 1) {
        trash_amount = 0;
    }

    for (int i = 0; i < trash_amount; i++) {
        setup_trash(i);
    }
}

// Calls all rubbish setup functions
void setup_rubbish() {
    setup_multiple_dust();
    setup_multiple_slime();
    setup_multiple_trash();
}

// Allows user to drop one additional piece of dust at a specified location
void drop_dust() {
        dx[dust_amount] = get_int("Enter the X coordinate of the dust:");
        dy[dust_amount] = get_int("Enter the Y coordinate of the dust:");
}

// Allows user to drop one additional piece of slime at a specified location
void drop_slime() {
        sx[slime_amount] = get_int("Enter the X coordinate of the slime:");
        sy[slime_amount] = get_int("Enter the Y coordinate of the slime:");
}

// Allows user to drop one additional piece of trash at a specified location
void drop_trash() {
        tx[trash_amount] = get_int("Enter the X coordinate of the trash:");
        ty[trash_amount] = get_int("Enter the Y coordinate of the trash:");
}

// Draws a piece of dust at coordinates taken from the x and y arrays
void draw_dust(int i) {
    draw_pixels(
                dx[i],
                dy[i],
                DUST_DIMENSION,
                DUST_DIMENSION,
                dust,
                true
    );
}

// Draws a piece of slime at coordinates taken from the x and y arrays
void draw_slime(int i) {
    draw_pixels(
        sx[i],
        sy[i],
        SLIME_DIMENSION,
        SLIME_DIMENSION,
        slime,
        true
    );
}

// Draws a piece of trash at coordinates taken from the x and y arrays
void draw_trash(int i) {
    draw_pixels(
        tx[i],
        ty[i],
        TRASH_WIDTH,
        TRASH_HEIGHT,
        trash,
        true
    );
}

// Calls draw_dust a specified amount of times
void draw_multiple_dust(int dust_amount) {
    for (int i = 0; i < dust_amount; i++) {
        draw_dust(dust_amount);
    }
}

// Calls draw_slime a specified amount of times
void draw_multiple_slime( int slime_amount ) {
    for (int i = 0; i < slime_amount; i++) {
        draw_slime(slime_amount);
    }
}

// Calls draw_trash a specified amount of times
void draw_multiple_trash( int trash_amount ) {
    for(int i = 0; i < trash_amount; i++) {
        draw_trash(trash_amount);
    }
}

// Calls all draw rubbish functions
void draw_all_rubbish() {
    draw_multiple_dust(dust_amount);
    draw_multiple_slime(slime_amount);
    draw_multiple_trash(trash_amount);
}

// Getter functions
int get_dust_amount() {
    return dust_amount;
}

int get_slime_amount() {
    return slime_amount;
}

int get_trash_amount() {
    return trash_amount;
}

int get_dust_dimension() {
    return DUST_DIMENSION;
}

int get_slime_dimension() {
    return SLIME_DIMENSION;
}

int get_trash_height() {
    return TRASH_HEIGHT;
}

int get_trash_width() {
    return TRASH_WIDTH;
}

char * get_trash_array() {
    return trash;
}

// Setter functions
void set_dust_amount(int amount) {
    dust_amount = amount;
}

void set_slime_amount(int amount) {
    slime_amount = amount;
}

void set_trash_amount(int amount) {
    trash_amount = amount;
}

