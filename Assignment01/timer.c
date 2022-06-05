#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <cab202_graphics.h>
#include <cab202_timers.h>

// Define global variables
// Sets the start time of the simulation
double start_time;

// Sets the time the simulation has run for
double elapsed_time;

// Time formatted in minutes
int minutes;

// Time formatted in seconds
int seconds;

// Uses get_current_time() to set the start_time variable
void setup_time() {
    start_time = get_current_time();
}

// Calculates the time elapsed and formats it into seconds and minutes
void time_elapsed() {
    elapsed_time = get_current_time() - start_time;
    seconds = (int)elapsed_time % 60;
    minutes = (int)elapsed_time/60;

}

// Getter functions
int get_minutes() {
    return minutes;
}

int get_seconds() {
    return seconds;
}

int get_start_time() {
    return start_time;
}