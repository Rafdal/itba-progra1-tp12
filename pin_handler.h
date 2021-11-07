#ifndef PIN_HANDLER_H
#define PIN_HANDLER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BUFFER 64	//Buffer size for Dynamic Memory where directions are stored

int pinMode(unsigned int pin, char* direction); //Set pin mode (out or in)
int killPin(unsigned int pin); //Unexport pin
void setPin(unsigned int pin, bool value); //Set pin with "value"
int statusPin (int pin); //Search for pin status and return 1 if it`s ON and 0 if it`s OFF

#endif