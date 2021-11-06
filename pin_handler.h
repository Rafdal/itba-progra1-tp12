#ifndef PIN_HANDLER_H
#define PIN_HANDLER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int pinMode(unsigned int pin, char* direction);
int killPin(unsigned int pin);
void setPin(unsigned int pin, bool value);
int statusPin (int pin);



#endif