#pragma once

/*
This module defines variables, functions, getters and setters to give
functionality to the three different types of rubbish in the simulation
dust, slime and trash.
*/

void setup_rubbish();

void drop_dust();
void drop_slime();
void drop_trash();

void draw_dust(int i);
void draw_slime(int i);
void draw_trash(int i);

void draw_multiple_dust(int dust_amount);
void draw_multiple_slime(int slime_amount);
void draw_multiple_trash(int trash_amount);
void draw_all_rubbish();

int get_dust_amount();
int get_slime_amount();
int get_trash_amount();

int get_dust_dimension();
int get_slime_dimension();
int get_trash_height();
int get_trash_width();

char * get_trash_array();

void set_dust_amount( int amount );
void set_slime_amount( int amount );
void set_trash_amount( int amount );



