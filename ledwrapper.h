//
// Created by agussolari on 6/11/21.
//

#ifndef ITBA_PROGRA1_TP12_LEDWRAPPER_H
#define ITBA_PROGRA1_TP12_LEDWRAPPER_H

#include <stdint.h>
#include <stdbool.h>

void toggleAll_w(void ); // Toggle all emulators
void setPin_w(uint8_t pin); // Set pin to ON
void offAll_w(void); // Turn Off all
void onAll_w(void); // Turn On all
void quit_w (void); //Unexport all leds



#endif //ITBA_PROGRA1_TP12_LEDWRAPPER_H
