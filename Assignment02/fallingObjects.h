// Holds the necessary functions and variables to draw and update
// falling objects within the program
#pragma once

void draw_asteroid(void);
void update_asteroid(void);

int get_asteroid_x(int asteroid_num);
int get_asteroid_y(int asteroid_num);
int get_asteroid_size();
char * get_asteroid_array();
int get_score();
int get_lives();
int get_asteroid_num();
int get_score();

void set_random_x();
void set_lives_cheat(int value);