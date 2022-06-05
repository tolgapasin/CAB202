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

#include "drawToScreen.h"
#include "collision.h"
#include "timer.h"
#include "serial.h"

// Define constant variables to be used within fallingObjects.c
#define ASTEROID_SIZE 7
#define MAX_ASTEROID 3

// Set global variables to be used within fallingObjects.c
int asteroid_num = 0;
int lives = 5;
int score = 0;
int asteroids_cleared[MAX_ASTEROID] = {0, 0, 0};
double asteroid_x[MAX_ASTEROID];
double asteroid_y[MAX_ASTEROID] = {-ASTEROID_SIZE, -ASTEROID_SIZE, -ASTEROID_SIZE};

// Set char array to be used when drawing an asteroid to the screen
char * asteroid = {
    "   #   "
    "  ###  "
    " ##### "
    "#######"
    " ##### "
    "  ###  "
    "   #   "
};

// Generates a random x coordinate for asteroids
// Uses get_current_time() to generate a seed
void set_random_x(int i) {
    srand(get_current_time());
    asteroid_x[i] = rand() % (LCD_X - 8);
}

// Draws all asteroids to the screen
// Asteroids start off screen
void draw_asteroid() {
    for (int i=0; i < MAX_ASTEROID; i++){
        draw_shape(asteroid_x[i], asteroid_y[i], ASTEROID_SIZE, ASTEROID_SIZE, asteroid, 1);
    }
    
}

// Updates the movement of asteroids
// Checks if the asteroid has collided with a plasma bolt
// or the deflector sheild
// Sends asteroids off screen with a random x coordinate
// if so
void update_asteroid() {
    for (int i=0; i < MAX_ASTEROID; i++) {

        if(asteroids_cleared[i] == 1) {
            set_random_x(i);
        }
        
        if (asteroid_y[i] < 32) { 
            asteroids_cleared[i] = 0;
            asteroid_y[i] += 0.3;
        } else {
            asteroid_y[i] = -ASTEROID_SIZE;
            asteroids_cleared[i] = 1;
            
            if (lives > 0) {
                lives--;
            }

        }

        if (asteroid_collision(i)) {
            asteroid_y[i] = -ASTEROID_SIZE;
            score++;
            asteroids_cleared[i] = 1;
        }

    }

}

// Returns the x coordinate for a specified asteroid
int get_asteroid_x(int asteroid_num) {
    return asteroid_x[asteroid_num];
}

// Returns the y coordinate for a specified asteroid
int get_asteroid_y(int asteroid_num) {
    return asteroid_y[asteroid_num];
}

// Returns asteroids size
int get_asteroid_size() {
    return ASTEROID_SIZE;
}

// Returns the char array used to draw the asteroid
char * get_asteroid_array() {
    return asteroid;
}

// Returns the amount of lives available
int get_lives() {
    return lives;
}

// Returns which asteroid is selected
int get_asteroid_num() {
    asteroid_num = 0;
    for (int i=0; i < MAX_ASTEROID; i++) {

        if ((asteroid_y[i] < 32) && (asteroid_y[i] > -ASTEROID_SIZE)) {
            asteroid_num++;
        } 

    }

    return asteroid_num;
}

// Returns the players score
int get_score() {
    return score;
}

// Set the amount of lives to a specified value
void set_lives_cheat(int value) {
    if (value >= 0) {
        lives = value;
    }
}

