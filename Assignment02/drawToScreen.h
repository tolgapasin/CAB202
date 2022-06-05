// Holds functions necessary to drawing information to the teensy and
// computer screen
#pragma once

void draw_double(uint8_t x, uint8_t y, double value, colour_t colour);
void draw_int(uint8_t x, uint8_t y, int value, colour_t colour);
void draw_shape( int left, int top, int width, int height, char bitmap[], int space_is_transparent);
void draw_dashed_line(int x1, int y1, int x2, int y2, colour_t colour);
void send_status_serial();
void send_controls_serial();