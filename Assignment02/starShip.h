// Holds the variables and functions necessary to setting up,
// drawing and updating the starfighter within the program
#pragma once

void setup_star_ship(void);
void draw_star_ship(void);
void erase_star_ship(void);
void update_star_ship(char charFromComp);

int get_star_ship_x();
int get_star_ship_y();

void set_star_ship_x(int x);
void set_star_ship_y(int y);