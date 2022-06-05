#pragma once

/*
This module defines variables, functions, getters and setters to give
functionality to the vacuum in this simulation.
*/

void draw_vacuum();
void draw_pixels(int, int, int, int, char[], bool);
void setup_vacuum();
void update_vacuum_pos();
void return_to_base();

double get_vacuum_vx();
double get_vacuum_vy();
double get_vacuum_vdx();
double get_vacuum_vdy();
int get_load_weight();
double get_vacuum_dir();
double get_vacuum_step();
double get_formatted_dir();
int get_vacuum_dimension();
double get_vacuum_speed();
char * get_vacuum_array();

void set_vacuum_vx(double);
void set_vacuum_vy(double);
void set_vacuum_vdx(double);
void set_vacuum_vdy(double);
void set_vacuum_weight(int weight);
void set_vacuum_dir(double direction);



