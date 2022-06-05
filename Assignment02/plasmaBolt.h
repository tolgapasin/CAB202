// Holds all variables and functions necessary to draw, update
// and shoot plasma bolts within the game.
#pragma once

void setup_plasma_bolt();
void draw_plasma_bolt();
void draw_plasma_bolts(char charFromComp);
void update_plasma_bolt(char charFromComp);
void shoot_plasma_bolt();

int get_plasma_x(int plasma_num);
int get_plasma_y(int plasma_num);
int get_plasma_bolt_size();
char * get_plasma_array();
int get_max_plasma_bolt();

int set_plasma_bolt_y(int plasma_num, int value);