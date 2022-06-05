#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <cab202_graphics.h>
#include <cab202_timers.h>
#include "vacuum.h"
#include "hud.h"
#include "trash.h"
#include "collided.h"
#include "helpers.h"
#include "timer.h"
#include "battery.h"

// Define global variables
// Booleans to show whether the game is over or paused
bool game_over = false;
bool paused = false;

// Sets the speed of the simulation when updating graphics
int delay = 10;

// Restricts the time the simulation can run for
int timeout = INT_MAX;

// Call all functions necessary to draw the simulation
void draw_all() {
    clear_screen();
    draw_border();
    draw_all_rubbish();
    draw_vacuum();
    draw_status_bar(get_formatted_dir(), get_vacuum_battery(), get_seconds(), get_minutes(), get_load_weight(), get_dust_amount(), get_slime_amount(), get_trash_amount());
    draw_charging_dock();
    show_screen();
}

// Set boolean value of pause to false
void pause_game(){
    paused = !paused;
}

// Brings up a goodbye message when called, then quits the game after a character is entered
void quit_game() {
    clear_screen();
    const char * message[] = {
        "Simulation terminated, goodbye!"
    };

    const int rows = 1;

    for (int i = 0; i < rows; i++) {
        int len = strlen(message[i]);
        int x = (screen_width() - len) / 2;
        int y = i + (screen_height() - rows) / 2;
        draw_formatted(x, y, message[i]);
    }

    show_screen();
    wait_char();
    game_over = true;
    return;
}

// Controls the movement of the vacuum according to user input of the i,j,k,l keys
void control_vacuum(int ch) {
        if ( ch == 'i') {
            set_vacuum_vy( get_vacuum_vy() - 1 );
        } else if ( ch == 'k') {
            set_vacuum_vy( get_vacuum_vy() + 1 );
        } else if ( ch == 'j') {
            set_vacuum_vx( get_vacuum_vx() - 1 );
        } else if ( ch == 'l') {
            set_vacuum_vx( get_vacuum_vx() + 1 );
        }
}

// Displays a help screen showing the possible controls of the simulation
void help_screen() {
    clear_screen();
    draw_formatted_lines(0, 0,
        "!!!!!!!!!!!!!!!!!!!!!!!!!\n"
        "!!!!! VaCu Sim 3000 !!!!!\n"
        "!!!!!!!!!!!!!!!!!!!!!!!!!\n"
        "\n"
        "Controls list:"
        "j, k, l, i: move vacuum left, down, right, up respectively\n"
        "m: set the delay between succesive invocations of the loop function in milliseconds\n"
        "o: set the time-out period, that is; the total permitted run time in milliseconds\n"
        "b: tell the vacuum to return to the charging dock\n"
        "v: move the device to a new location\n"
        "w: change the weight of rubish currently held by the vacuum\n"
        "y: change the battery level of the vacuum\n"
        "d: drop a piece of dust to a specified location\n"
        "s: drop a piece of slime to a specified location\n"
        "t: drop a piece of trash to a specified location\n"
        "p: pause or resume the vacuums movement\n"
        "r: restart\n"
        "q: quit\n"
        "?: display the help screen\n"
        "Press a key to return to the game."
    );

    show_screen();
    while (get_char() > 0) {}
    while (wait_char() <= 0) {}
}

// Changes the timeout value of the simulation, specified by user input
void change_timeout() {
    timeout = get_int("How many seconds shall the program run?");
}

// Checks if the game has timed out
bool timed_out() {
    return get_current_time() - get_start_time() >= timeout;
}

// Changes the delay value between loops, specified by user input
void change_delay() {
    delay = get_int("New delay (milliseconds)?");

    if (delay < 0) delay = 10;
}

// Changes the x and y coordinates of the vacuum, specified by user input
void change_vacuum_location() {
    set_vacuum_vx( get_int("Vacuum x?") );
    set_vacuum_vy( get_int("Vacuum y?") );
    set_vacuum_dir( get_int("Vacuum direction?") );
}

// Changes the vacuum battery status, specified on user input
void change_vacuum_battery() {
    set_vacuum_battery( get_int("Battery level?") );
}

// void return_to_base() {
    
// }

// Changes the current load weight on the vacuum, specified by user input
void change_vacuum_weight() {
    set_vacuum_weight( get_int("New load weight?") );
}

// Forces a exit screen giving the user two options, quit or reset the simulation.
// Called when battery life equals 0
void force_quit_or_restart() {
    int ch = get_char();
    if (ch == 'q') {

    } else if (ch == 'r') {
        
    }
}


// Defines which key taken from user input will call which function
void take_input(int ch) {
    if (ch == 'p') {
        pause_game();
    } else if(paused) {
        control_vacuum(ch);
    } else if (ch == 'q') {
        quit_game();
    } else if (ch == '?') {
        help_screen();
    } else if (ch == 'd') {
        drop_dust();
    } else if (ch == 's') {
        drop_slime();
    } else if (ch == 't') {
        drop_trash();
    } else if (ch == 'o') {
        change_timeout();
    } else if (ch == 'm') {
        change_delay();
    } else if (ch == 'v') {
        change_vacuum_location();
    } else if (ch == 'y') {
        change_vacuum_battery();
    } else if ( ch == 'b' ) {
        return_to_base();
    } else if (ch == 'w') {
        change_vacuum_weight();
    }
}

// Calls the necessary functions to setup the simulation and sets paused to true
void setup () {
    paused = true;
    setup_time();
    setup_vacuum();
    setup_rubbish();
    draw_all();
}

// Calls the necessary functions to update the game after one iteration of the loop
// Checks for user input and if the game is paused
void loop() {
    time_elapsed();
    update_battery();
    int ch = get_char();

    if ( ch == 'r' ) {
        clear_screen();
        setup();
    } else if ( ch >= ' ' ) {
        take_input( ch );
    } else if ( !paused ) {
        update_vacuum_pos();
        bounce_dock();
    } else if (get_vacuum_battery() == 0) {
        force_quit_or_restart();
    }

    draw_all();
}

// Defines a random variable
// Sets up the simulation
// Updates the simulation if game over and time out are both false
int main() {
    srand(get_current_time());
    setup_screen();
    setup();

    while ( !game_over & !timed_out() ) {
        loop();
        timer_pause( delay );
    }

    return 0;
}
