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
#include "usb_serial.h"
#include "cab202_adc.h"

#include "fallingObjects.h"
#include "collision.h"
#include "drawToScreen.h"
#include "plasmaBolt.h"
#include "starShip.h"
#include "timer.h"
#include "serial.h"
#include "pwm.h"
#include "debounce.h"

// Set global variables to be used in main.c
int paused = 1;
int introSkip = 0;
int game_status_on = 0;
int game_status_sent = 0;
int game_started = 0;
int game_over = 0;
char charFromComp;
int pwm_level = 800;
int pwm_max = 1023;


// Calls all draw functions at the same time
void draw_all(char charFromComp) {
    draw_dashed_line(0, 39, 83, 39, FG_COLOUR);
    draw_star_ship();
    draw_asteroid();
    draw_plasma_bolt();
}

// Calls all update functions at the same time
void update_all(char charFromComp) {
    update_asteroid();
    update_star_ship(charFromComp);
    update_plasma_bolt(charFromComp);
}

// Pauses game
void pause_game() {
    paused = !paused;
    _delay_ms(200);
}

// Sets game over status to 1
void set_game_over() {
    if(get_lives() == 0) {
        game_over = 1;
    }
}

// Setup joystick/buttons on the teensy for input
void set_input() {
    CLEAR_BIT(DDRD, 0); 
    CLEAR_BIT(DDRB, 1); 
    CLEAR_BIT(DDRB, 0); 
    CLEAR_BIT(DDRD, 1); 
    CLEAR_BIT(DDRF, 6); 
    CLEAR_BIT(DDRD, 6);
}

// Check if input has been entered for each relevant button and respond appropriately
void take_input(char charFromComp) {
    if (BIT_IS_SET(PINB, 0) || charFromComp == 'p') {
            pause_game();      
     } else if ((BIT_IS_SET(PINB, 7) || charFromComp == 's')) {
         _delay_ms(10);
        game_status_on = !game_status_on;
    } else if (BIT_IS_SET(PINF, 6) || charFromComp == 'r') {
        introSkip = !introSkip;
        if (game_over) {
            game_over = 0;
        }
    } else if (charFromComp == '?') {
        send_controls_serial();
    } else if (charFromComp == 'l') {
        send_over_serial("Lives: ");
        charFromComp = usb_serial_getchar();
        char buffer[5];
        snprintf(buffer, sizeof(buffer), "%c", charFromComp);
        send_over_serial(buffer);
        set_lives_cheat(charFromComp);
    }
}

// Draw the necessary components to show the introduction screen
// Turn the backlight on using PWM
void introduction_display(char charFromComp) {
    set_pwm_level(pwm_level);
    draw_string(3, 3, "n9737917", FG_COLOUR);
    draw_string(3, 11, "Asteroid", FG_COLOUR);
    draw_string(3, 18, "Apocalypse", FG_COLOUR);
    show_screen();

    while (introSkip == 0) {
        charFromComp = usb_serial_getchar();
        take_input(charFromComp);
        _delay_ms(10);
    }

    clear_screen();
}

// Draws the necessary components to show the game over screen
// Fades off the backlight using PWM
// Turns LED's off
void game_over_message() {
    draw_string(17, 20, "GAME OVER!", FG_COLOUR);
    show_screen();
    SET_BIT(PORTB, 2);
    SET_BIT(PORTB, 3);
    _delay_ms(2000);
    CLEAR_BIT(PORTB, 2);
    CLEAR_BIT(PORTB, 3);

    while (pwm_level < pwm_max) {
        pwm_level += 10;
        set_pwm_level(pwm_level);
        _delay_ms(20);
    }

}

// Draws the necessary components to show the game status on the teensy screen
void game_status(char charFromComp) {
    take_input(charFromComp);
    char buffer[50];
    time_elapsed();
    snprintf(buffer, sizeof(buffer), "Time: %02d:%02d", get_minutes(), get_seconds());
    draw_string(3, 3, buffer, FG_COLOUR);
    draw_string(3, 11, "Lives: ", FG_COLOUR);
    draw_int(35, 11, get_lives(), FG_COLOUR);
    draw_string(3, 19, "Score: ", FG_COLOUR);
    draw_int(35, 19, get_score(), FG_COLOUR);
    show_screen();
    game_status_on |= (BIT_IS_SET(PINB, 7) || charFromComp == 's');
    take_input(charFromComp);
    _delay_ms(10);
    clear_screen();
}

// Sets up basic teensy functionality (clockspeed, adc, etc.)
// Calls all functions necessary to setting up the game
// Draws some components to the screen
void setup(void) {
    set_clock_speed(CPU_8MHz);
    adc_init();
    lcd_init(LCD_DEFAULT_CONTRAST);
    lcd_clear();
    setup_serial();
    charFromComp = usb_serial_getchar();
    set_input();
    take_input(charFromComp);
    setup_pwm();
    setup_timer();
    setup_star_ship();
    setup_plasma_bolt();
    introduction_display(charFromComp);
    draw_all(charFromComp);
    set_random_x();
    show_screen();
}

// The main process of the game to be called on loop
// Calls update functions
// Checks if game has started, is paused or if the game status is on
// Sets game to game over status when necessary
void process(void) {
    if (game_started == 0) {
        send_status_serial();
        send_over_serial("Game started!\n\n\r");
        game_started = 1;
    }

    charFromComp = usb_serial_getchar();
    take_input(charFromComp);
    clear_screen(); 
    update_all(charFromComp);
    draw_all(charFromComp);
    show_screen();

    if (paused) {
        CLEAR_BIT(TIMSK1, TOIE1);
        CLEAR_BIT(TCCR1B, CS12);
        CLEAR_BIT(TCCR1B, CS11);
        CLEAR_BIT(TCCR1B, CS10);
    } 

    if (!paused) {
        SET_BIT(TIMSK1, TOIE1);
        TCCR1B = 4;
    }

    if(game_status_on) {
        CLEAR_BIT(TIMSK1, TOIE1);
        CLEAR_BIT(TCCR1B, CS12);
        CLEAR_BIT(TCCR1B, CS11);
        CLEAR_BIT(TCCR1B, CS10);
    }

    if(!game_status_on) {
        SET_BIT(TIMSK1, TOIE1);
        TCCR1B = 4;
    }

    set_game_over();
}

// Calls all necessary functions for the game to run (setup, process)
// Calls process on a loop while game is not over
// Reacts accordinly to if game is over or game status is on
int main(void) {
    setup();

	while ( !game_over ) {
        while(paused != 0) {
            charFromComp = usb_serial_getchar();
            take_input(charFromComp);
            draw_all(charFromComp);
            show_screen();
         } 

        while(game_status_on) { 
            charFromComp = usb_serial_getchar();
            take_input(charFromComp);
            game_status(charFromComp);
            if(!game_status_sent) {
                send_status_serial();
                game_status_sent = 1;
            }
        }

        game_status_sent = 0;
        process();
		_delay_ms(10);
	}

    if(game_over) {  
            send_status_serial();
            send_over_serial("Game over!");  
            clear_screen();
            game_over_message();
            set_pwm_level(1023);
        }

	return 0;
}

