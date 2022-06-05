// Holds the variables and functions necessary to setup a 
// usb serial link between the teeny and the computer and 
// comunicate between them
#pragma once

void setup_serial();
void send_over_serial(char * message);