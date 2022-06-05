#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <cab202_graphics.h>
#include <cab202_timers.h>
#include "timer.h"

// Define global variable to store battery percentage
int battery_life = 100;

// Update the battery life by decrementing it every second
void update_battery() {
    int seconds = get_seconds();
    int updated_seconds = seconds + 1;
    if (seconds == updated_seconds)  {
        updated_seconds = seconds;
        battery_life--;
    }
}

// Get batter_life variable
int get_vacuum_battery() {
    return battery_life;
}

// Set battery_life variable
void set_vacuum_battery(int level) {
    battery_life = level;
}