#pragma once

/*
This module defines variables, functions, getters and setters to give
functionality to the heads up display of this simulation.
*/

void draw_status_bar(double vacuum_dir, int vacuum_battery, int seconds, int minutes, int vacuum_weight, int dust_amount, int slime_amount, int trash_amount);
void draw_border();
void draw_charging_dock();

char * get_dock_array();

int get_dock_width();
int get_dock_height();

double get_dockx();
double get_docky();
